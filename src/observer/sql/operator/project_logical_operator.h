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
// Created by WangYunlai on 2022/12/08.
//

#pragma once

#include <memory>
#include <vector>

#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"

/**
 * @brief project 表示投影运算
 * @ingroup LogicalOperator
 * @details 从表中获取数据后，可能需要过滤，投影，连接等等。
 */
class ProjectLogicalOperator : public LogicalOperator
{
public:
  ProjectLogicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions);
  virtual ~ProjectLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::PROJECTION; }

  std::vector<std::unique_ptr<Expression>>       &expressions() { return expressions_; }
  const std::vector<std::unique_ptr<Expression>> &expressions() const { return expressions_; }

  void set_multi_tables_flag() { multi_tables_flag_ = 1; }
  int get_multi_tables_flag() const { return multi_tables_flag_; }

  void set_has_view_flag() { has_view_flag_ = 1; }
  int get_has_view_flag() const { return has_view_flag_; }
private:
  int multi_tables_flag_ = 0;
  int has_view_flag_ = 0;
};
