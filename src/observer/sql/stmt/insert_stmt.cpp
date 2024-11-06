/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db, const InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  if (table->view()) {
    View *view = table->view();
    if (view->col_names().size() != inserts.values.size()) {
      LOG_WARN("column number not match. expect %d, but got %d", view->col_names().size(), inserts.values.size());
      return RC::INVALID_ARGUMENT;
    }

    std::vector<int> indexes;
    Table *insert_table = view->handle_view_insert(indexes);
    if (nullptr == insert_table) {
      LOG_WARN("failed to get insert table");
      return RC::INTERNAL;
    }

    Value *view_insert_values = new Value[indexes.size()];
    for (size_t i = 0; i < indexes.size(); i++) {
      if (indexes[i] != -1) {
        view_insert_values[i] = inserts.values[indexes[i]];
      } else {
        Value null_value;
        null_value.set_null();
        view_insert_values[i] = null_value;
      }
    }

    stmt = new InsertStmt(insert_table, view_insert_values, indexes.size());
    return RC::SUCCESS;
  }

  // check the fields number
  const Value     *values     = inserts.values.data();
  const int        value_num  = static_cast<int>(inserts.values.size());
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();
  if (field_num != value_num) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }

  // ensure that non-nullable fields do not receive null values
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field = table_meta.field(i + table_meta.sys_field_num());
    if (field->nullable() == false && values[i].get_null() == 1) {
      LOG_WARN("non-nullable field receives null value. field name=%s", field->name());
      return RC::FIELD_NOT_NULL_VIOLATION;
    }
  }

  // everything alright
  stmt = new InsertStmt(table, values, value_num);
  return RC::SUCCESS;
}
