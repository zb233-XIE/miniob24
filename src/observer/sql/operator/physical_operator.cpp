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
// Created by WangYunlai on 2022/11/18.
//

#include "sql/operator/physical_operator.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include <memory>

std::string physical_operator_type_name(PhysicalOperatorType type)
{
  switch (type) {
    case PhysicalOperatorType::TABLE_SCAN: return "TABLE_SCAN";
    case PhysicalOperatorType::INDEX_SCAN: return "INDEX_SCAN";
    case PhysicalOperatorType::NESTED_LOOP_JOIN: return "NESTED_LOOP_JOIN";
    case PhysicalOperatorType::EXPLAIN: return "EXPLAIN";
    case PhysicalOperatorType::PREDICATE: return "PREDICATE";
    case PhysicalOperatorType::INSERT: return "INSERT";
    case PhysicalOperatorType::DELETE: return "DELETE";
    case PhysicalOperatorType::PROJECT: return "PROJECT";
    case PhysicalOperatorType::STRING_LIST: return "STRING_LIST";
    case PhysicalOperatorType::HASH_GROUP_BY: return "HASH_GROUP_BY";
    case PhysicalOperatorType::SCALAR_GROUP_BY: return "SCALAR_GROUP_BY";
    case PhysicalOperatorType::AGGREGATE_VEC: return "AGGREGATE_VEC";
    case PhysicalOperatorType::GROUP_BY_VEC: return "GROUP_BY_VEC";
    case PhysicalOperatorType::PROJECT_VEC: return "PROJECT_VEC";
    case PhysicalOperatorType::TABLE_SCAN_VEC: return "TABLE_SCAN_VEC";
    case PhysicalOperatorType::EXPR_VEC: return "EXPR_VEC";
    default: return "UNKNOWN";
  }
}

std::string PhysicalOperator::name() const { return physical_operator_type_name(type()); }

std::string PhysicalOperator::param() const { return ""; }

void PhysicalOperator::add_helper_tuple(const Tuple *tuple)
{
  helper_tuples_.push_back(tuple);
}

void PhysicalOperator::add_helper_tuples(std::vector<const Tuple *> &tuples)
{
  for (const Tuple *tuple : tuples) {
    helper_tuples_.push_back(tuple);
  }
}

std::vector<const Tuple *> &PhysicalOperator::get_helper_tuples()
{
  return helper_tuples_;
}

void PhysicalOperator::helper_tuples_pushdown()
{
  for (auto &child_oper : children_) {
    for (const Tuple *tuple : helper_tuples_) {
      child_oper->add_helper_tuple(tuple);
    }
    child_oper->helper_tuples_pushdown();
  }
}

void PhysicalOperator::helper_tuple_clear_rec()
{
  helper_tuples_.clear();
  for (auto &child_oper : children_) {
    child_oper->helper_tuple_clear_rec();
  }
}
