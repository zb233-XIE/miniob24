/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/6/13.
//

#include "sql/executor/create_table_executor.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/optimize_stage.h"
#include "sql/stmt/create_table_stmt.h"
#include "storage/db/db.h"

RC CreateTableExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_TABLE,
      "create table executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  CreateTableStmt *create_table_stmt = static_cast<CreateTableStmt *>(stmt);
  std::unique_ptr<PhysicalOperator> physical_oper;

  if (create_table_stmt->has_subquery()) {
    RC rc = generate_physical_plan(session->get_current_db(), create_table_stmt, physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to generate physical plan for subquery. rc=%d:%s", rc, strrc(rc));
      return rc;
    }

    if (create_table_stmt->attr_infos().empty()) {
      rc = get_attrs_from_subq(session->get_current_db(), create_table_stmt, physical_oper);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get attributes from subquery. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
    }
  }

  const char *table_name = create_table_stmt->table_name().c_str();
  RC rc = session->get_current_db()->create_table(table_name, create_table_stmt->attr_infos(), create_table_stmt->storage_format());
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create table. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  if (create_table_stmt->has_subquery()) {
    Table *table = session->get_current_db()->find_table(table_name);
    if (table == nullptr) {
      LOG_WARN("table not found: %s", table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    rc = insert_records_from_subq(physical_oper, table);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert records from subquery. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
  }

  return rc;
}

RC CreateTableExecutor::generate_physical_plan(Db *db, CreateTableStmt *create_stmt, std::unique_ptr<PhysicalOperator> &oper) {
  RC rc = RC::SUCCESS;
  SelectStmt *select_stmt = create_stmt->get_subquery();

  LogicalPlanGenerator logical_generator;
  PhysicalPlanGenerator physical_generator;
  OptimizeStage        opt_stage;

  unique_ptr<LogicalOperator> logical_oper;
  unique_ptr<PhysicalOperator> physical_oper;
  rc = logical_generator.create(select_stmt, logical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create logical operator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  rc = opt_stage.rewrite(logical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to rewrite logical operator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  rc = physical_generator.create(*logical_oper, physical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create physical operator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  oper = std::move(physical_oper);
  return rc;
}

RC CreateTableExecutor::get_attrs_from_subq(Db *db, CreateTableStmt *create_stmt, std::unique_ptr<PhysicalOperator> &physical_oper)
{
  RC rc = RC::SUCCESS;

  TupleSchema schema;
  physical_oper->tuple_schema(schema);
  if (schema.cell_num() == 0) {
    LOG_WARN("subquery result is empty");
    return RC::SCHEMA_FIELD_MISSING;
  }

  std::set<std::string> field_name_sets;

  // get attribute infos from schema
  std::vector<AttrInfoSqlNode> attr_infos;
  for (int i = 0; i < schema.cell_num(); i++) {
    TupleCellSpec spec = schema.cell_at(i);
    std::string field_name = spec.alias();

    std::string table_name;
    std::string column_name;
    size_t dot_pos = field_name.find('.');
    if (dot_pos != std::string::npos) {
      table_name = field_name.substr(0, dot_pos);
      column_name = field_name.substr(dot_pos + 1);
    } else {
      table_name = create_stmt->default_subq_table_name();
      column_name = field_name;
    }

    Table *table = db->find_table(table_name.c_str());
    if (table == nullptr) {
      LOG_WARN("table not found: %s", table_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    const FieldMeta *field_meta = table->table_meta().field(column_name.c_str());
    if (field_meta == nullptr) {
      LOG_WARN("field not found: %s.%s", table_name.c_str(), column_name.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    if (field_name_sets.find(field_meta->name()) != field_name_sets.end()) {
      LOG_WARN("duplicate field name: %s", field_name.c_str());
      return RC::DUPLICATE_FIELD_NAME;
    }
    field_name_sets.insert(field_meta->name());

    AttrInfoSqlNode attr_info;
    attr_info.name = field_meta->name();
    attr_info.type = field_meta->type();
    attr_info.length = field_meta->len();
    attr_info.nullable = field_meta->nullable();
    attr_infos.push_back(attr_info);
  }

  create_stmt->set_attr_infos(attr_infos);
  return rc;
}

RC CreateTableExecutor::insert_records_from_subq(std::unique_ptr<PhysicalOperator> &physical_oper, Table *table) {
  RC rc = physical_oper->open(nullptr);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open physical operator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  while ((rc = physical_oper->next()) == RC::SUCCESS) {
    Tuple *tuple = physical_oper->current_tuple();
    int cell_num = tuple->cell_num();
    Value val;
    std::vector<Value> vals;
    for (int i = 0; i < cell_num; i++) {
      tuple->cell_at(i, val);
      vals.push_back(val);
    }

    Record record;
    table->make_record(cell_num, vals.data(), record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to make record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }

    table->insert_record(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record into table. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
  }

  rc = physical_oper->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close physical operator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  return rc;
}
