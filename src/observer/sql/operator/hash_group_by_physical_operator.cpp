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
// Created by WangYunlai on 2024/05/30.
//

#include "common/lang/memory.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/operator/hash_group_by_physical_operator.h"
#include "sql/expr/expression_tuple.h"
#include "sql/expr/composite_tuple.h"
#include "sql/parser/parse_defs.h"
#include <compare>
#include <algorithm>
#include <memory>

using namespace std;
using namespace common;

HashGroupByPhysicalOperator::HashGroupByPhysicalOperator(
    vector<unique_ptr<Expression>> &&group_by_exprs, vector<Expression *> &&expressions, unique_ptr<Expression> &having_check)
    : GroupByPhysicalOperator(std::move(expressions)), group_by_exprs_(std::move(group_by_exprs)), having_check_(std::move(having_check))
{
}

RC HashGroupByPhysicalOperator::open(Trx *trx)
{
  ASSERT(children_.size() == 1, "group by operator only support one child, but got %d", children_.size());

  // having
  analysis_having_check(having_check_.get());

  PhysicalOperator &child = *children_[0];
  RC                rc    = child.open(trx);
  if (OB_FAIL(rc)) {
    LOG_INFO("failed to open child operator. rc=%s", strrc(rc));
    return rc;
  }

  ExpressionTuple<Expression *> group_value_expression_tuple(value_expressions_);

  ValueListTuple group_by_evaluated_tuple;

  while (OB_SUCC(rc = child.next())) {
    Tuple *child_tuple = child.current_tuple();
    if (nullptr == child_tuple) {
      LOG_WARN("failed to get tuple from child operator. rc=%s", strrc(rc));
      return RC::INTERNAL;
    }

    // 找到对应的group
    GroupType *found_group = nullptr;
    rc                     = find_group(*child_tuple, found_group);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to find group. rc=%s", strrc(rc));
      return rc;
    }

    // 计算需要做聚合的值
    group_value_expression_tuple.set_tuple(child_tuple);

    // 计算聚合值
    GroupValueType &group_value = get<1>(*found_group);
    rc = aggregate(get<0>(group_value), group_value_expression_tuple);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to aggregate values. rc=%s", strrc(rc));
      return rc;
    }

    // 处理having
    if (having_check_) {
      // 处理having_check_中的聚合函数
      ExpressionTuple<Expression *> having_value_expression_tuple(having_value_expressions_);
      having_value_expression_tuple.set_tuple(child_tuple);
      rc = aggregate(get_having_aggregator_list(idx_), having_value_expression_tuple);
      if (OB_FAIL(rc)) {
        LOG_WARN("failed to aggregate values. rc=%s", strrc(rc));
        return rc;
      }
      // 处理having_check_中的非聚合函数，只更新一次，也就是第一次
      CompositeTuple &composite_tuple = get_composite_tuple(idx_);
      if (composite_tuple.cell_num() == 0) {
        // ExpressionTuple<Expression *> having_filed_expression_tuple(having_field_expressions_);
        ValueListTuple                having_evaluated_tuple;
        // having_filed_expression_tuple.set_tuple(child_tuple);
        rc = ValueListTuple::make(*child_tuple, having_evaluated_tuple);
        if (OB_FAIL(rc)) {
          LOG_WARN("failed to get values from expression tuple. rc=%s", strrc(rc));
          return rc;
        }
        composite_tuple.add_tuple(make_unique<ValueListTuple>(std::move(having_evaluated_tuple)));
      }
    }
  }

  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  }

  if (OB_FAIL(rc)) {
    LOG_WARN("failed to get next tuple. rc=%s", strrc(rc));
    return rc;
  }

  // 得到最终聚合后的值
  idx_ = 0;
  for (GroupType &group : groups_) {
    GroupValueType &group_value = get<1>(group);
    rc = evaluate(group_value);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to evaluate group value. rc=%s", strrc(rc));
      return rc;
    }

    // 处理having中的聚合函数的结果，仿照evaluate
    if (having_aggregator_lists_.size() > 0) {
      vector<TupleCellSpec> aggregator_names;
      for (Expression *expr : having_aggregate_expressions_) {
        aggregator_names.emplace_back(expr->name());
      }

      AggregatorList &aggregators           = get_having_aggregator_list(idx_);
      CompositeTuple &composite_value_tuple = get_composite_tuple(idx_);

      ValueListTuple evaluated_tuple;
      vector<Value>  values;
      for (unique_ptr<Aggregator> &aggregator : aggregators) {
        Value value;
        rc = aggregator->evaluate(value);
        if (OB_FAIL(rc)) {
          LOG_WARN("failed to evaluate aggregator. rc=%s", strrc(rc));
          return rc;
        }
        values.emplace_back(value);
      }

      evaluated_tuple.set_cells(values);
      evaluated_tuple.set_names(aggregator_names);

      composite_value_tuple.add_tuple(make_unique<ValueListTuple>(std::move(evaluated_tuple)));
    }


    idx_++;
  }

  // having:将不满足having的group去掉
  // idx_ = 0;
  // if (having_check_) {
  //   // 下面的代码有bug，见https://zhuanlan.zhihu.com/p/400434509
  //   // 用erase效率很低，不如创建一个新的groups，用来存符合条件的group
  //   for (auto it = groups_.begin(); it != groups_.end();) {
  //     Value           value;
  //     CompositeTuple &composite_value_tuple = get_composite_tuple(idx_);
  //     having_check_->get_value(composite_value_tuple, value);
  //     if (value.get_boolean() == false) {
  //       it = groups_.erase(it);
  //     }
  //     it++;
  //     idx_++;
  //   }
  // }

  idx_ = 0;
  current_group_ = groups_.begin();
  first_emited_  = false;
  return rc;
}

RC HashGroupByPhysicalOperator::next()
{
flag:
  if (current_group_ == groups_.end()) {
    return RC::RECORD_EOF;
  }

  if (first_emited_) {
    ++current_group_;
    ++idx_;
  } else {
    first_emited_ = true;
  }
  if (current_group_ == groups_.end()) {
    return RC::RECORD_EOF;
  }

  // 如果能到达这里，说明current_group有效
  // 但是还要加入having的判断
  if (having_check_) {
    Value           value;
    CompositeTuple &composite_value_tuple = get_composite_tuple(idx_);
    having_check_->get_value(composite_value_tuple, value);
    if (value.get_boolean() == false) {
      goto flag;
    }
  }

  return RC::SUCCESS;
}

RC HashGroupByPhysicalOperator::close()
{
  children_[0]->close();
  LOG_INFO("close group by operator");
  return RC::SUCCESS;
}

Tuple *HashGroupByPhysicalOperator::current_tuple()
{
  if (current_group_ != groups_.end()) {
    GroupValueType &group_value = get<1>(*current_group_);
    return &get<1>(group_value);
  }
  return nullptr;
}

// 提取having_check_中的表达式
void HashGroupByPhysicalOperator::analysis_having_check(Expression *expr)
{
  if (expr == nullptr) {
    return;
  }
  ExprType expr_type = expr->type();
  if (expr_type == ExprType::FIELD) {
    having_field_expressions_.push_back(expr);
  } else if (expr_type == ExprType::AGGREGATION) {
    having_aggregate_expressions_.push_back(expr);
    AggregateExpr *aggregate_expr = static_cast<AggregateExpr *>(expr);
    having_value_expressions_.push_back(aggregate_expr->child().get());
  } else if (expr->type() == ExprType::CONJUNCTION) {
    ConjunctionExpr *conjunction_expr = static_cast<ConjunctionExpr *>(expr);
    auto &children = conjunction_expr->children();
    for (auto &child_expr : children) {
      analysis_having_check(child_expr.get());
    }
  } else if (expr->type() == ExprType::COMPARISON) {
    ComparisonExpr *comparision_expr = static_cast<ComparisonExpr *>(expr);
    analysis_having_check(comparision_expr->left().get());
    analysis_having_check(comparision_expr->right().get());
  }
}

RC HashGroupByPhysicalOperator::find_group(const Tuple &child_tuple, GroupType *&found_group)
{
  idx_ = 0;
  found_group = nullptr;

  RC rc = RC::SUCCESS;

  ExpressionTuple<unique_ptr<Expression>> group_by_expression_tuple(group_by_exprs_);
  ValueListTuple                          group_by_evaluated_tuple;
  group_by_expression_tuple.set_tuple(&child_tuple);
  rc = ValueListTuple::make(group_by_expression_tuple, group_by_evaluated_tuple);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to get values from expression tuple. rc=%s", strrc(rc));
    return rc;
  }

  // 找到对应的group
  for (GroupType &group : groups_) {
    int compare_result = 0;
    rc                 = group_by_evaluated_tuple.compare(get<0>(group), compare_result);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to compare group by values. rc=%s", strrc(rc));
      return rc;
    }

    if (compare_result == 0) {
      found_group = &group;
      break;
    }
    idx_++;
  }

  // 如果没有找到对应的group，创建一个新的group
  if (nullptr == found_group) {
    AggregatorList aggregator_list;
    create_aggregator_list(aggregator_list);

    ValueListTuple child_tuple_to_value;
    rc = ValueListTuple::make(child_tuple, child_tuple_to_value);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to make tuple to value list. rc=%s", strrc(rc));
      return rc;
    }

    CompositeTuple composite_tuple;
    composite_tuple.add_tuple(make_unique<ValueListTuple>(std::move(child_tuple_to_value)));
    groups_.emplace_back(std::move(group_by_evaluated_tuple), 
                         GroupValueType(std::move(aggregator_list), std::move(composite_tuple)));
    found_group = &groups_.back();

    // 对having的处理
    if (having_check_) {
      // 仿照create_aggregator_list，该group对应的aggregator
      AggregatorList having_aggregator_list;
      having_aggregator_list.clear();
      having_aggregator_list.reserve(having_aggregate_expressions_.size());
      ranges::for_each(having_aggregate_expressions_, [&having_aggregator_list](Expression *expr) {
        auto *aggregate_expr = static_cast<AggregateExpr *>(expr);
        having_aggregator_list.emplace_back(aggregate_expr->create_aggregator());
      });
      having_aggregator_lists_.emplace_back(std::move(having_aggregator_list));

      // 该group对应的composite tuple
      CompositeTuple having_composite_tuple;
      composite_tuple_list_.emplace_back(std::move(having_composite_tuple));
      idx_ = groups_.size() - 1;
    }
  }

  return rc;
}