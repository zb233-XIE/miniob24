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

#pragma once

#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include <memory>
#include <unordered_map>
#include <vector>

class Db;
class Table;
class FieldMeta;

struct FilterObj
{
  bool  is_attr;
  Field field;
  Value value;

  void init_attr(const Field &field)
  {
    is_attr     = true;
    this->field = field;
  }

  void init_value(const Value &value)
  {
    is_attr     = false;
    this->value = value;
  }
};

class FilterUnit
{
public:
  FilterUnit() = default;
  ~FilterUnit() {}

  void set_comp(CompOp comp) { comp_ = comp; }

  CompOp comp() const { return comp_; }

  int flag() const { return neither_; }

  void set_left(const FilterObj &obj) { left_ = obj; }
  void set_right(const FilterObj &obj) { right_ = obj; }
  void set_flag(const int flag) { neither_ = flag; }
  void set_left_expr(Expression *expr) { left_expr_ = expr; }
  void set_right_expr(Expression *expr) { right_expr_ = expr; }

  const FilterObj &left() const { return left_; }
  const FilterObj &right() const { return right_; }
  Expression *left_expr() const { return left_expr_; }
  Expression *right_expr() const { return right_expr_; }


private:
  CompOp    comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
  int neither_;
  Expression *left_expr_;
  Expression *right_expr_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const { return filter_units_; }

  int is_and() { return is_and_; }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt, int is_and = 1);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode &condition, FilterUnit *&filter_unit);

private:
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
  int is_and_ = 1;
};
