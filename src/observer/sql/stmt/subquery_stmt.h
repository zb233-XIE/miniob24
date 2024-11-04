#pragma once

#include "common/value.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/parser/parse_defs.h"
#include <vector>

// 仿照filter stmt

class SubqueryUnit
{
public:
  SubqueryUnit() = default;
  ~SubqueryUnit() {}

  void set_comp(CompOp comp) { comp_ = comp; }

  CompOp comp() const { return comp_; }

  void set_left_expr(Expression *expr) { left_expr_ = expr; }
  void set_right_expr(Expression *expr) { right_expr_ = expr; }

  Expression *left_expr() const { return left_expr_; }
  Expression *right_expr() const { return right_expr_; }

private:
  CompOp comp_;
  Expression *left_expr_;
  Expression *right_expr_;
};

class SubqueryStmt
{
public:
  SubqueryStmt() = default;
  virtual ~SubqueryStmt();

public:
  const std::vector<SubqueryUnit *> &subquery_units() const { return subquery_units_; }

  int is_and() { return is_and_; }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode *conditions, int condition_num, SubqueryStmt *&stmt, int is_and = 1);

  static RC create_subquery_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode &condition, SubqueryUnit *&subquery_unit);

private:
  std::vector<SubqueryUnit *> subquery_units_; // 默认当前都是AND关系
  int is_and_ = 1;
};