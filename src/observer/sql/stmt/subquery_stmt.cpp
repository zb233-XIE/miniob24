#include "sql/stmt/subquery_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"

SubqueryStmt::~SubqueryStmt()
{
  for (SubqueryUnit *unit : subquery_units_) {
    delete unit;
  }
  subquery_units_.clear();
}

RC SubqueryStmt::create_subquery_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, SubqueryUnit *&subquery_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;

  subquery_unit = new SubqueryUnit;

  // condition中的表达式已绑定，比如UnboundFieldExpr已经转换为了FiledExpr
  subquery_unit->set_left_expr(condition.left_expr);
  subquery_unit->set_right_expr(condition.right_expr);

  subquery_unit->set_comp(comp);

  return rc;
}

RC SubqueryStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, SubqueryStmt *&stmt, int is_and)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  SubqueryStmt *tmp_stmt = new SubqueryStmt();
  tmp_stmt->is_and_ = is_and;
  for (int i = 0; i < condition_num; i++) {
    SubqueryUnit *subquery_unit = nullptr;

    rc = create_subquery_unit(db, default_table, tables, conditions[i], subquery_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create subquery unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->subquery_units_.push_back(subquery_unit);
  }

  stmt = tmp_stmt;
  return rc;
}