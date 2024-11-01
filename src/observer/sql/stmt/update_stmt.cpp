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
#include "common/type/attr_type.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

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

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char              *table_name = update.relation_name.c_str();
  std::vector<std::string> attr_names;
  std::vector<Value>       values;
  for (const SetClauseSqlNode &set_clause : update.set_clauses) {
    attr_names.push_back(set_clause.attribute_name);
    values.push_back(set_clause.value);
  }

  bool undefined_attr_type = false;
  for (const Value &value : values) {
    if (value.attr_type() == AttrType::UNDEFINED) {
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
  const std::vector<FieldMeta> &field_metas = *table->table_meta().output_field_metas();
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
    if (values[i].attr_type() != update_fields[i].type()) {
      LOG_WARN("value used to update record type %d does not match field `%s` type %d",
        values[i].attr_type(), update_fields[i].name(), update_fields[i].type());
      if(values[i].attr_type() == AttrType::CHARS && update_fields[i].type() == AttrType::TEXTS){
        // do nothing
      } else {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
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
