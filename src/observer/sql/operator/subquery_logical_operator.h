#pragma once

#include "common/value.h"
#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

class SubqueryLogicalOperator : public LogicalOperator
{
public:
  SubqueryLogicalOperator(std::unique_ptr<Expression> expression, CompOp comp, int left_is_expr);
  virtual ~SubqueryLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::SUBQUERY; }
  void set_comp(CompOp comp) { comp_ = comp; }
  void set_values(std::vector<Value> &values) { values_.swap(values); }
  std::vector<Value> &get_values() { return values_; }
  std::unique_ptr<Expression> &expr() { return expression_; }
  CompOp comp() { return comp_; }
  int left_is_expr() { return left_is_expr_; }

private:
  CompOp comp_;
  std::unique_ptr<Expression> expression_;
  std::vector<Value> values_;
  int left_is_expr_;
};