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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/optimize_stage.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

UpdateStmt::UpdateStmt(Table *table, const std::vector<Value> &values, FilterStmt *filter_stmt, const std::vector<FieldMeta> &fields)
: table_(table), values_(values), filter_stmt_(filter_stmt), fields_(fields)
{}

UpdateStmt::~UpdateStmt()
{
  if (filter_stmt_ != nullptr) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::get_subquery_value(Db *db, ParsedSqlNode *subquery, Value &value) {
  Stmt *subquery_stmt = nullptr;
  RC rc = Stmt::create_stmt(db, *subquery, subquery_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create subquery stmt. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  SelectStmt *subquery_select_stmt = dynamic_cast<SelectStmt *>(subquery_stmt);
  if (subquery_select_stmt == nullptr) {
    LOG_WARN("subquery stmt is not a select stmt");
    return RC::INVALID_ARGUMENT;
  }

  LogicalPlanGenerator logical_generator;
  PhysicalPlanGenerator physical_generator;
  OptimizeStage opt_stage;

  unique_ptr<LogicalOperator> logical_oper;
  unique_ptr<PhysicalOperator> physical_oper;
  rc = logical_generator.create(subquery_select_stmt, logical_oper);
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

  // cast physical operator to project operator unique ptr
  ProjectPhysicalOperator *project_oper = dynamic_cast<ProjectPhysicalOperator *>(physical_oper.get());
  rc = project_oper->open(nullptr);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open subquery operator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  std::vector<Value> values;
  while (project_oper->next() == RC::SUCCESS) {
    Tuple *tuple = project_oper->current_tuple();
    if (tuple == nullptr) {
      LOG_WARN("subquery result is empty");
      return RC::NOTFOUND;
    }

    sql_debug("update-select subquery get a tuple: %s", tuple->to_string().c_str());
    Value val;
    rc = tuple->cell_at(0, val);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get subquery value. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
    values.push_back(val);
  }

  if (values.empty()) {
    sql_debug("subquery result is empty, set value to null");
    value.set_value(Value(0));
    // value.set_null();
    return RC::SUCCESS;
  }

  if (values.size() > 1) {
    sql_debug("subquery result has %d rows, error", values.size());
    return RC::INVALID_ARGUMENT;
  }

  value = values[0];
	return rc;
}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt)
{
  const char              *table_name = update.relation_name.c_str();
  std::vector<std::string> attr_names;
  std::vector<Value>       values;
  for (const SetClauseSqlNode &set_clause : update.set_clauses) {
    attr_names.push_back(set_clause.attribute_name);
    if (set_clause.has_subquery) {
      Value value;
			RC rc = get_subquery_value(db, set_clause.subquery, value);
			if (rc != RC::SUCCESS) {
				LOG_WARN("failed to get subquery value. rc=%d:%s", rc, strrc(rc));
				return rc;
			}
      values.push_back(value);
    } else {
      values.push_back(set_clause.value);
    }
  }

  bool undefined_attr_type = false;
  for (const Value &value : values) {
    if (value.attr_type() == AttrType::UNDEFINED && !value.get_null()) {  // invalid date value
      undefined_attr_type = true;
      break;
    }
  }

  if (db == nullptr || table_name == nullptr || undefined_attr_type) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check whether the field exists
  const std::vector<FieldMeta> &field_metas = *table->table_meta().field_metas();
  // const FieldMeta              *update_field     = nullptr;
  std::vector<FieldMeta> update_fields;

  for (size_t i = 0; i < attr_names.size(); i++) {
    bool update_col_found = false;
    for (const FieldMeta &field_meta : field_metas) {
      if (strcmp(field_meta.name(), attr_names[i].c_str()) == 0) {
        update_fields.push_back(field_meta);
        update_col_found = true;
        break;
      }
    }
    if (!update_col_found) {
      LOG_WARN("attempt to update a non-existent col of a record. table_name: %s, col_name: %s",
        table_name, attr_names[i].c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    // check whether the type of field and value is the same
    if (values[i].attr_type() != update_fields[i].type() && !values[i].get_null()) {
      LOG_WARN("value used to update record type %d does not match field `%s` type %d",
        values[i].attr_type(), update_fields[i].name(), update_fields[i].type());
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    // check if the field is not null and value is null
    if (values[i].get_null() && !update_fields[i].nullable()) {
      LOG_WARN("field `%s` is not nullable, but value is null", update_fields[i].name());
      return RC::FIELD_NOT_NULL_VIOLATION;
    }
  }

  // 6. 绑定upadte.conditions中的表达式
  BinderContext binder_context;
  binder_context.add_table(table);

  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder               expression_binder(binder_context);

  for (ConditionSqlNode &condition : update.conditions) {
    RC rc = RC::SUCCESS;
    if (condition.neither) {
      vector<unique_ptr<Expression>> left_bound_expressions;
      vector<unique_ptr<Expression>> right_bound_expressions;
      std::unique_ptr<Expression>    left_expr  = std::unique_ptr<Expression>(condition.left_expr);
      std::unique_ptr<Expression>    right_expr = std::unique_ptr<Expression>(condition.right_expr);
      rc = expression_binder.bind_expression(left_expr, left_bound_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind expression failed. rc=%s", strrc(rc));
        return rc;
      }
      rc = expression_binder.bind_expression(right_expr, right_bound_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind expression failed. rc=%s", strrc(rc));
        return rc;
      }
      condition.left_expr  = left_bound_expressions[0].release();
      condition.right_expr = right_bound_expressions[0].release();
    }
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map[table_name] = table;

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  stmt = new UpdateStmt(table, values, filter_stmt, update_fields);
  return rc;
}
