/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include <common/log/log.h>
#include <memory>
#include <utility>
#include <vector>

#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/group_by_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/limit_logical_operator.h"

#include "sql/parser/parse_defs.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/subquery_stmt.h"
#include "sql/stmt/stmt.h"

#include "sql/expr/expression_iterator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/index/index.h"

using namespace std;
using namespace common;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);

      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);

      rc = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);

      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);

      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);

      rc = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLEMENTED;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(OrderByStmt *order_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator = order_stmt != nullptr ? make_unique<OrderByLogicalOperator>(order_stmt->items()) : nullptr;
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> *last_oper = nullptr;

  unique_ptr<LogicalOperator> table_oper(nullptr);
  last_oper = &table_oper;

  bool vector_order_by           = false;
  int  vector_order_by_limit     = -1;
  bool vector_order_by_index_hit = false;
  // 在JonLogicalOperator和TableGetLogicalOperator之间插入PredicateLogicalOperator
  size_t                      idx    = 0;
  const std::vector<Table *> &tables = select_stmt->tables();
  for (Table *table : tables) {
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY));
    if (table_oper == nullptr) {
      if (select_stmt->order_by() != nullptr) {
        auto       *order_by_stmt  = select_stmt->order_by();
        const auto &order_by_items = order_by_stmt->items();
        if (order_by_items.size() == 1 && order_by_items[0].expression != nullptr) {
          vector_order_by         = true;
          // treat vector type order by specially
          // eg. SELECT embedding FROM items ORDER BY L2_DISTANCE('[1,2,3]', C1) LIMIT 3;
          // if index hit in: project -> vector_index_scan
          // if not           project -> limit -> order_by -> table_scan
          auto table_get_oper_ptr = dynamic_cast<TableGetLogicalOperator *>(table_get_oper.get());
          vector_order_by_limit   = select_stmt->limits();

          auto                        *vector_arith_expr = dynamic_cast<ArithmeticExpr *>(order_by_items[0].expression);
          std::unique_ptr<Expression> &left_expr         = vector_arith_expr->left();
          std::unique_ptr<Expression> &right_expr        = vector_arith_expr->right();

          // extract field name
          UnboundFieldExpr *ub_field_expr = nullptr;
          if (left_expr->type() == ExprType::UNBOUND_FIELD) {
            ASSERT(right_expr->type() == ExprType::VALUE, "vector search order by clause semantic error");
            ub_field_expr = static_cast<UnboundFieldExpr *>(left_expr.get());
          } else if (right_expr->type() == ExprType::UNBOUND_FIELD) {
            ASSERT(left_expr->type() == ExprType::VALUE, "vector search order by clause semantic error");
            ub_field_expr = static_cast<UnboundFieldExpr *>(right_expr.get());
          }

          if (ub_field_expr != nullptr) {
            // find index, check index algorithm
            Index *index = table_get_oper_ptr->table()->find_index_by_field(ub_field_expr->field_name());
            if (index != nullptr) {
              auto index_algorithm = index->index_meta().alrgorithm();
              auto query_algorithm = vector_arith_expr->arithmetic_type();
              switch (query_algorithm) {
                case ArithmeticExpr::Type::L2_DIS: {
                  if (index_algorithm == DISTANCE_ALGO::L2_DISTANCE) {
                    vector_order_by_index_hit = true;
                  }
                } break;
                case ArithmeticExpr::Type::COS_DIS: {
                  if (index_algorithm == DISTANCE_ALGO::COSINE_DISTANCE) {
                    vector_order_by_index_hit = true;
                  }
                } break;
                case ArithmeticExpr::Type::INN_PDT: {
                  if (index_algorithm == DISTANCE_ALGO::INNER_PRODUCT) {
                    vector_order_by_index_hit = true;
                  }
                } break;
                default: {
                  vector_order_by_index_hit = false;
                }
              }

              if(vector_order_by_index_hit){
                unique_ptr<Expression>                   exp(vector_arith_expr);
                std::vector<std::unique_ptr<Expression>> predicate_vector;
                predicate_vector.push_back(std::move(exp));
                table_get_oper_ptr->set_predicates(std::move(predicate_vector));
              }
            }
          }

          if(vector_order_by_index_hit){
            table_get_oper_ptr->set_limit(select_stmt->limits());
          } else {
            table_get_oper_ptr->set_limit(-1);
          }
        }
      }
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));

      if (select_stmt->join_filter_stmts().size()) {
        unique_ptr<LogicalOperator> predicate_oper;
        RC                          rc = create_plan(select_stmt->join_filter_stmts()[idx++], predicate_oper);
        if (OB_FAIL(rc)) {
          LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
          return rc;
        }
        if (predicate_oper) {
          predicate_oper->add_child(unique_ptr<LogicalOperator>(join_oper));
          table_oper = std::move(predicate_oper);
        }
      } else {
        table_oper = unique_ptr<LogicalOperator>(join_oper);
      }
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper;
  }

  // 子查询的predicate_oper2
  unique_ptr<LogicalOperator> predicate_oper2;

  rc = create_plan(select_stmt->subquery_stmt(), predicate_oper2);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper2) {
    if (*last_oper) {
      predicate_oper2->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper2;
  }

  // having
  unique_ptr<LogicalOperator> having_predicate_oper;
  rc = create_plan(select_stmt->having_filter_stmt(), having_predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  unique_ptr<Expression> having_expression;
  if (having_predicate_oper) {
    having_expression = std::move(having_predicate_oper->expressions().front());
  }

  unique_ptr<LogicalOperator> group_by_oper;
  rc = create_group_by_plan(select_stmt, group_by_oper, having_expression);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (group_by_oper) {
    if (*last_oper) {
      group_by_oper->add_child(std::move(*last_oper));
    }
    last_oper = &group_by_oper;
  }

  unique_ptr<LogicalOperator> project_oper;
  project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()));
  ASSERT(project_oper != nullptr, "");
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }
  if (tables.size() > 1) {
    auto * project_oper_ptr = dynamic_cast<ProjectLogicalOperator *>(project_oper.get());
    project_oper_ptr->set_multi_tables_flag();
  }
  last_oper = &project_oper;

  unique_ptr<LogicalOperator> order_by_oper;
  if (!vector_order_by_index_hit) {
    rc = create_plan(select_stmt->order_by(), order_by_oper);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to create order by logical plan. rc=%s", strrc(rc));
      return rc;
    }
  }
  if (order_by_oper) {
    order_by_oper->add_child(std::move(*last_oper));
    last_oper = &order_by_oper;
  }

  if (vector_order_by && !vector_order_by_index_hit) {
    // order by operator must exist!
    unique_ptr<LogicalOperator> limit_oper;
    rc = create_limit_plan(vector_order_by_limit, limit_oper);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to create limit logical plan for vector serach");
      return rc;
    }
    ASSERT(limit_oper != nullptr,"");
    ASSERT(*last_oper != nullptr, "");
    limit_oper->add_child(std::move(*last_oper));
    logical_operator = std::move(limit_oper);
  } else {
    logical_operator = std::move(*last_oper);
  }

  return RC::SUCCESS;
}

// 先将将FilterUnit左右两个FilterObj转换为Expression
// 如果是attr，转换为FieldExpr；否则转换为ValueExpr
// 再将两个Expression以及比较操作符生成ComparisonExpr
// 利用AND（目前只支持AND）将它们连接成ConjunctionExpr
// 将其作为参数（Expression）构造出PredicateLogicalOperator，使logical_operator指向它
RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC                                  rc = RC::SUCCESS;
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
    if (filter_unit->flag()) {
      left  = unique_ptr<Expression>(filter_unit->left_expr());
      right = unique_ptr<Expression>(filter_unit->right_expr());
    } else {
      const FilterObj &filter_obj_left  = filter_unit->left();
      const FilterObj &filter_obj_right = filter_unit->right();

      left = unique_ptr<Expression>(filter_obj_left.is_attr
                                        ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
                                        : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));

      right = unique_ptr<Expression>(filter_obj_right.is_attr
                                         ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
                                         : static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));
    }

    ValueExpr *left_value_expr  = dynamic_cast<ValueExpr *>(filter_unit->left_expr());
    bool       left_null        = left_value_expr != nullptr && left_value_expr->is_null();
    ValueExpr *right_value_expr = dynamic_cast<ValueExpr *>(filter_unit->right_expr());
    bool       right_null       = right_value_expr != nullptr && right_value_expr->is_null();
    bool       has_null         = left_null || right_null;

    if (left->value_type() != right->value_type() && !has_null) {
      auto left_to_right_cost = implicit_cast_cost(left->value_type(), right->value_type());
      auto right_to_left_cost = implicit_cast_cost(right->value_type(), left->value_type());
      if (left_to_right_cost <= right_to_left_cost && left_to_right_cost != INT32_MAX) {
        ExprType left_type = left->type();
        auto     cast_expr = make_unique<CastExpr>(std::move(left), right->value_type());
        if (left_type == ExprType::VALUE) {
          Value left_val;
          if (OB_FAIL(rc = cast_expr->try_get_value(left_val))) {
            LOG_WARN("failed to get value from left child", strrc(rc));
            return rc;
          }
          left = make_unique<ValueExpr>(left_val);
        } else {
          left = std::move(cast_expr);
        }
      } else if (right_to_left_cost < left_to_right_cost && right_to_left_cost != INT32_MAX) {
        ExprType right_type = right->type();
        auto     cast_expr  = make_unique<CastExpr>(std::move(right), left->value_type());
        if (right_type == ExprType::VALUE) {
          Value right_val;
          if (OB_FAIL(rc = cast_expr->try_get_value(right_val))) {
            LOG_WARN("failed to get value from right child", strrc(rc));
            return rc;
          }
          right = make_unique<ValueExpr>(right_val);
        } else {
          right = std::move(cast_expr);
        }

      } else {
        rc = RC::UNSUPPORTED;
        LOG_WARN("unsupported cast from %s to %s", attr_type_to_string(left->value_type()), attr_type_to_string(right->value_type()));
        return rc;
      }
    }

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return rc;
}

// 仿照参数为FilterStmt的create_plan，目的是构建出表达式为ConjunctionExpr的PredicateLogicalOperator
// ConjunctionExpr中是多个SubqueryExpr
RC LogicalPlanGenerator::create_plan(SubqueryStmt *subquery_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;

  const std::vector<SubqueryUnit *>  &subquery_units = subquery_stmt->subquery_units();
  std::vector<unique_ptr<Expression>> subquery_exprs;
  for (SubqueryUnit *subquery_unit : subquery_units) {
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
    left  = unique_ptr<Expression>(subquery_unit->left_expr());
    right = unique_ptr<Expression>(subquery_unit->right_expr());

    // 对于left和right中的stmt，递归地创建其logical plan
    if (left->type() == ExprType::BOUND_SUBQUERY) {
      auto                        row_left = static_cast<BoundSubqueryExpr *>(left.get());
      Stmt                       *sub_stmt = row_left->stmt();
      unique_ptr<LogicalOperator> sub_logical_operator;
      create(sub_stmt, sub_logical_operator);
      row_left->set_logical_operator(sub_logical_operator);
    }

    if (right->type() == ExprType::BOUND_SUBQUERY) {
      auto                        row_right = static_cast<BoundSubqueryExpr *>(right.get());
      Stmt                       *sub_stmt  = row_right->stmt();
      unique_ptr<LogicalOperator> sub_logical_operator;
      create(sub_stmt, sub_logical_operator);
      row_right->set_logical_operator(sub_logical_operator);
    }

    ComparisonExpr *cmp_expr = new ComparisonExpr(subquery_unit->comp(), std::move(left), std::move(right));
    subquery_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!subquery_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, subquery_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return rc;
}

int LogicalPlanGenerator::implicit_cast_cost(AttrType from, AttrType to)
{
  if (from == to) {
    return 0;
  }
  return DataType::type_instance(from)->cast_cost(to);
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table        *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                      *table       = delete_stmt->table();
  FilterStmt                 *filter_stmt = delete_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                 *table                 = update_stmt->table();
  FilterStmt            *filter_stmt           = update_stmt->filter_stmt();
  std::vector<Value>     values                = update_stmt->values();
  std::vector<FieldMeta> fields                = update_stmt->fields();
  bool                   update_internal_error = update_stmt->update_internal_error();

  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, values, fields, update_internal_error));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> child_oper;

  Stmt *child_stmt = explain_stmt->child();

  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_limit_plan(int limits, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator = unique_ptr<LogicalOperator>(new LimitLogicalOperator(limits));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_group_by_plan(
    SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator, unique_ptr<Expression> &having_expr)
{
  vector<unique_ptr<Expression>>             &group_by_expressions = select_stmt->group_by();
  vector<Expression *>                        aggregate_expressions;
  vector<unique_ptr<Expression>>             &query_expressions = select_stmt->query_expressions();
  function<RC(std::unique_ptr<Expression> &)> collector         = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr.get() == nullptr) {
      return rc;
    }
    if (expr->type() == ExprType::AGGREGATION) {
      expr->set_pos(aggregate_expressions.size() + group_by_expressions.size());
      aggregate_expressions.push_back(expr.get());
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, collector);
    return rc;
  };

  function<RC(std::unique_ptr<Expression> &)> bind_group_by_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    for (size_t i = 0; i < group_by_expressions.size(); i++) {
      auto &group_by = group_by_expressions[i];
      if (expr->type() == ExprType::AGGREGATION) {
        break;
      } else if (expr->equal(*group_by)) {
        expr->set_pos(i);
        continue;
      } else {
        rc = ExpressionIterator::iterate_child_expr(*expr, bind_group_by_expr);
      }
    }
    return rc;
  };

  bool                                        found_unbound_column = false;
  function<RC(std::unique_ptr<Expression> &)> find_unbound_column  = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr.get() == nullptr) {
      return rc;
    }
    if (expr->type() == ExprType::AGGREGATION) {
      // do nothing
    } else if (expr->pos() != -1) {
      // do nothing
    } else if (expr->type() == ExprType::FIELD) {
      found_unbound_column = true;
    } else {
      rc = ExpressionIterator::iterate_child_expr(*expr, find_unbound_column);
    }
    return rc;
  };

  for (unique_ptr<Expression> &expression : query_expressions) {
    bind_group_by_expr(expression);
  }

  for (unique_ptr<Expression> &expression : query_expressions) {
    find_unbound_column(expression);
  }

  // collect all aggregate expressions
  for (unique_ptr<Expression> &expression : query_expressions) {
    collector(expression);
  }

  if (group_by_expressions.empty() && aggregate_expressions.empty()) {
    // 既没有group by也没有聚合函数，不需要group by
    return RC::SUCCESS;
  }

  if (found_unbound_column) {
    LOG_WARN("column must appear in the GROUP BY clause or must be part of an aggregate function");
    return RC::INVALID_ARGUMENT;
  }

  // 如果只需要聚合，但是没有group by 语句，需要生成一个空的group by 语句

  auto group_by_oper =
      make_unique<GroupByLogicalOperator>(std::move(group_by_expressions), std::move(aggregate_expressions));
  if (having_expr) {
    group_by_oper->set_having_check(having_expr);
  }
  logical_operator = std::move(group_by_oper);
  return RC::SUCCESS;
}
