#pragma once

#include "common/value.h"
#include "sql/stmt/stmt.h"
#include "sql/parser/parse_defs.h"
#include <vector>

class SubqueryStmt
{
public:
  SubqueryStmt(Expression *expr, Stmt *sub_stmt, CompOp comp, int left_is_expr)
      : expr_(expr), sub_stmt_(sub_stmt), comp_(comp), left_is_expr_(left_is_expr)
  {
  }

  SubqueryStmt(Expression *expr, std::vector<Value> &values, CompOp comp, int left_is_expr)
      : expr_(expr), comp_(comp), left_is_expr_(left_is_expr)
  {
    values_.swap(values);
  }
  ~SubqueryStmt() {}

  Expression *expr() { return expr_; }
  Stmt *sub_stmt() { return sub_stmt_; }
  CompOp comp() const { return comp_; }
  std::vector<Value> &values() { return values_; }
  int left_is_expr() const { return left_is_expr_; }

  RC self_check();

private:
  Expression *expr_; // 未释放，来源yacc处理expressin的$$->emplace_back($1);
  Stmt *sub_stmt_ = nullptr;
  std::vector<Value> values_;
  CompOp comp_;
  int left_is_expr_;
};