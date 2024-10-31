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
  CompOp comp() const {return comp_; }
  Stmt *stmt() const { return stmt_; }
  Expression *expr() const { return expr_; }
  std::vector<Value> &values() { return values_; }
  int left_is_expr() { return left_is_expr_; }

  void set_left_is_expr(int left_is_expr) { left_is_expr_ = left_is_expr; }
  void set_expr(Expression *expr) { expr_ = expr; }
  void set_stmt(Stmt *stmt) { stmt_ = stmt; }
  void set_values(std::vector<Value> &values) { values_.swap(values); }

  RC check();

private:
  int left_is_expr_;
  CompOp comp_;
  Expression *expr_;
  Stmt *stmt_;
  std::vector<Value> values_;
};

class SubqueryStmt
{
public:
  SubqueryStmt() = default;
  virtual ~SubqueryStmt();

public:
  const std::vector<SubqueryUnit *> &subquery_units() const { return subquery_units_; }

public:
  
  static RC create_subquery_unit(ConditionSqlNode &condition, Expression *bound_expr, Stmt *stmt, SubqueryUnit *&filter_unit);

  RC add_unit(ConditionSqlNode &condition, Expression *bound_expr, Stmt *stmt);

  RC check_unit(SubqueryUnit *unit);

private:
  std::vector<SubqueryUnit *> subquery_units_; // 默认当前都是AND关系
};

// class SubqueryStmt
// {
// public:
//   SubqueryStmt(Expression *expr, Stmt *sub_stmt, CompOp comp, int left_is_expr)
//       : expr_(expr), sub_stmt_(sub_stmt), comp_(comp), left_is_expr_(left_is_expr)
//   {
//   }

//   SubqueryStmt(Expression *expr, std::vector<Value> &values, CompOp comp, int left_is_expr)
//       : expr_(expr), comp_(comp), left_is_expr_(left_is_expr)
//   {
//     values_.swap(values);
//   }
//   ~SubqueryStmt() {}

//   Expression *expr() { return expr_; }
//   Stmt *sub_stmt() { return sub_stmt_; }
//   CompOp comp() const { return comp_; }
//   std::vector<Value> &values() { return values_; }
//   int left_is_expr() const { return left_is_expr_; }

//   RC self_check();

// private:
//   Expression *expr_; // 未释放，来源yacc处理expressin的$$->emplace_back($1);
//   Stmt *sub_stmt_ = nullptr;
//   std::vector<Value> values_;
//   CompOp comp_;
//   int left_is_expr_;
// };