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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class SubqueryStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const { return tables_; }
  FilterStmt                 *filter_stmt() const { return filter_stmt_; }
  std::vector<FilterStmt *>   join_filter_stmts() const { return join_filter_stmts_; }
  FilterStmt                 *having_filter_stmt() const { return having_filter_stmt_; }
  SubqueryStmt               *subquery_stmt() const { return subquery_stmt_; }
  const std::vector<bool> &is_aliased() const { return is_aliased_; }
  const std::vector<std::string> &aliases() const { return aliases_; }

  std::vector<std::unique_ptr<Expression>> &query_expressions() { return query_expressions_; }
  std::vector<std::unique_ptr<Expression>> &group_by() { return group_by_; }
  OrderByStmt                              *order_by() const { return order_by_; }

  int limits() const { return limits_; }

  void set_tables(const std::vector<Table *> tables) { tables_ = tables; }

private:
  std::vector<std::unique_ptr<Expression>> query_expressions_;
  std::vector<Table *>                     tables_;
  std::vector<bool>                        is_aliased_;
  std::vector<std::string>                 aliases_;
  FilterStmt                              *filter_stmt_ = nullptr;
  std::vector<std::unique_ptr<Expression>> group_by_;
  std::vector<FilterStmt *>                join_filter_stmts_;
  FilterStmt                              *having_filter_stmt_ = nullptr;
  SubqueryStmt                            *subquery_stmt_      = nullptr;
  OrderByStmt                             *order_by_           = nullptr;
  int                                      limits_             = INT_MAX;
};
