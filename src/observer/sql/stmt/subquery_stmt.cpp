#include "sql/stmt/subquery_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"

RC SubqueryUnit::check()
{
  if (stmt_ == nullptr) {
    return RC::SUCCESS;
  }
  SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt_);
  if (comp_ == CompOp::IN || comp_ == CompOp::NOT_IN) {
    if (select_stmt->query_expressions().size() != 1) {
      return RC::INTERNAL;
    }
  } else if (comp_ == CompOp::EXISTS || comp_ == CompOp::NOT_EXISTS) {
    // empty
  } else {
    if (select_stmt->query_expressions().size() != 1) {
      return RC::INTERNAL;
    }

    Expression *expr = select_stmt->query_expressions().front().get();
    if (expr->type() != ExprType::AGGREGATION) {
      return RC::INTERNAL;
    }
  }
  return RC::SUCCESS;
}

SubqueryStmt::~SubqueryStmt()
{
  for (SubqueryUnit *unit : subquery_units_) {
    delete unit;
  }
  subquery_units_.clear();
}

RC SubqueryStmt::add_unit(ConditionSqlNode &condition, Expression *bound_expr, Stmt *stmt)
{
  RC rc = RC::SUCCESS;
  SubqueryUnit *subquery_unit = nullptr;

  rc = create_subquery_unit(condition, bound_expr, stmt, subquery_unit);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create subquery unit. condition");
    return rc;
  }
  rc = subquery_unit->check();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create subquery unit. condition");
    return rc;
  }
  subquery_units_.push_back(subquery_unit);
  return rc;
}

RC SubqueryStmt::create_subquery_unit(ConditionSqlNode &condition, Expression *bound_expr, Stmt *stmt, SubqueryUnit *&subquery_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }
  
  subquery_unit = new SubqueryUnit;

  subquery_unit->set_left_is_expr(condition.left_is_expr);
  subquery_unit->set_comp(comp);
  subquery_unit->set_expr(bound_expr);
  subquery_unit->set_stmt(stmt);
  subquery_unit->set_values(condition.values);

  return rc;
}