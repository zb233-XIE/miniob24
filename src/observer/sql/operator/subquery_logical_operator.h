#pragma once

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
  std::unique_ptr<Expression> &expr() { return expression_; }
  CompOp comp() { return comp_; }
  int left_is_expr() { return left_is_expr_; }

private:
  CompOp comp_;
  std::unique_ptr<Expression> expression_;
  int left_is_expr_;
};