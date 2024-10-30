#include "sql/stmt/subquery_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"

RC SubqueryStmt::self_check()
{
  if (sub_stmt_ == nullptr) {
    return RC::SUCCESS;
  }
  SelectStmt *select_stmt = static_cast<SelectStmt *>(sub_stmt_);
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