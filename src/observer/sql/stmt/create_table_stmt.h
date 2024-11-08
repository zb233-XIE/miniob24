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

#pragma once

#include <string>
#include <vector>

#include "common/types.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateTableStmt : public Stmt
{
public:
  CreateTableStmt(
      const std::string &table_name, const std::vector<AttrInfoSqlNode> &attr_infos, StorageFormat storage_format)
      : table_name_(table_name), attr_infos_(attr_infos), storage_format_(storage_format), has_subquery_(false), subquery_(nullptr)
  {}
  CreateTableStmt(const std::string &table_name, SelectStmt *subquery)
      : table_name_(table_name), storage_format_(StorageFormat::ROW_FORMAT), has_subquery_(true), subquery_(subquery)
  {}
  virtual ~CreateTableStmt() = default;

  StmtType type() const override { return StmtType::CREATE_TABLE; }

  const std::string                  &table_name() const { return table_name_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }
  void                                set_attr_infos(const std::vector<AttrInfoSqlNode> &attr_infos) { attr_infos_ = attr_infos; }
  const StorageFormat                 storage_format() const { return storage_format_; }
  bool                                has_subquery() const { return has_subquery_; }
  SelectStmt                         *get_subquery() const { return subquery_; }
  void                                set_default_subq_table_name(const std::string &table_name) { default_subq_table_name_ = table_name; }
  const std::string                  &default_subq_table_name() const { return default_subq_table_name_; }

  static RC            create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt);
  static StorageFormat get_storage_format(const char *format_str);

private:
  std::string                  table_name_;
  std::vector<AttrInfoSqlNode> attr_infos_;
  StorageFormat                storage_format_;
  bool                         has_subquery_;
  SelectStmt                   *subquery_;
  std::string                  default_subq_table_name_;
};