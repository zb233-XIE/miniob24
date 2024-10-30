#include "sql/operator/subquery_logical_operator.h"

SubqueryLogicalOperator::SubqueryLogicalOperator(std::unique_ptr<Expression> expression, CompOp comp, int left_is_expr)
    : comp_(comp), expression_(std::move(expression)), left_is_expr_(left_is_expr)
{}