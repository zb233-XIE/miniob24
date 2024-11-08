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

#pragma once

#include <string>

#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field_meta.h"

struct CreateIndexSqlNode;
class Table;
class FieldMeta;

/**
 * @brief 在向量列上创建索引的语句，一次仅支持在一列上创建
 * @ingroup Statement
 */
class CreateVectorIndexStmt : public Stmt
{
public:
  CreateVectorIndexStmt(Table *table, const FieldMeta &field_meta, const std::string &index_name,
      DISTANCE_ALGO algorithm, int centroids, int probes)
      : table_(table),
        field_meta_(field_meta),
        index_name_(index_name),
        algorithm_(algorithm),
        centroids_(centroids),
        probes_(probes)
  {}

  virtual ~CreateVectorIndexStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VECTOR_INDEX; }

  Table             *table() const { return table_; }
  DISTANCE_ALGO     algorithm() const { return algorithm_; }
  int               centroids() const { return centroids_; }
  int               probes() const { return probes_; }
  const FieldMeta   &field_meta() const { return field_meta_; }
  const std::string &index_name() const { return index_name_; }

public:
  static RC create(Db *db, const CreateVectorIndexSqlNode &create_index, Stmt *&stmt);

private:
  Table        *table_ = nullptr;
  FieldMeta     field_meta_;
  std::string   index_name_;
  DISTANCE_ALGO algorithm_;
  int           centroids_;
  int           probes_;
};
