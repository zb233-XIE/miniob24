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
// Created by Wangyunlai on 2023/4/25.
//

#include "sql/stmt/create_vector_index_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/type/attr_type.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <vector>

using namespace std;
using namespace common;

RC CreateVectorIndexStmt::create(Db *db, const CreateVectorIndexSqlNode &create_vector_index, Stmt *&stmt)
{
  stmt = nullptr;

  bool has_blank_attr = false;
  if (is_blank(create_vector_index.attribute.c_str())) {
    has_blank_attr = true;
  }

  const char *table_name = create_vector_index.relation_name.c_str();
  if (is_blank(table_name) || is_blank(create_vector_index.index_name.c_str()) || has_blank_attr) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, index name=%s, attribute name=%s",
        db, table_name, create_vector_index.index_name.c_str(), create_vector_index.attribute.c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check whether vector field exists
  const string    &attr_name  = create_vector_index.attribute;
  const FieldMeta *field_meta = table->table_meta().out_field(attr_name.c_str());
  if (nullptr == field_meta) {
    LOG_WARN("no such field in table. db=%s, table=%s, field name=%s", 
                db->name(), table_name, attr_name.c_str());
    return RC::SCHEMA_FIELD_NOT_EXIST;
  } else if (field_meta->type() != AttrType::VECTORS) {
    LOG_WARN("db=%s, table=%s, field name= %s is not vector type",
                db->name(), table_name, attr_name.c_str());
    return RC::INVALID_ARGUMENT;
  }

  Index *index = table->find_index(create_vector_index.index_name.c_str());
  if (nullptr != index) {
    LOG_WARN("index with name(%s) already exists. table name=%s", create_vector_index.index_name.c_str(), table_name);
    return RC::SCHEMA_INDEX_NAME_REPEAT;
  }

  stmt = new CreateVectorIndexStmt(table,
      (*field_meta),
      create_vector_index.index_name,
      create_vector_index.distance_algo,
      create_vector_index.centroids,
      create_vector_index.probes);
  return RC::SUCCESS;
}
