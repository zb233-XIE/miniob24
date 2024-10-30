#pragma once
#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include <memory>

class SubqueryPhysicalOperator : public PhysicalOperator
{
public:
  SubqueryPhysicalOperator(std::unique_ptr<Expression> expression, CompOp comp, int left_is_expr);
  virtual ~SubqueryPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::SUBQUERY; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  void set_values(std::vector<Value> &values) { values_.swap(values); }

  // RC tuple_schema(TupleSchema &schema) const override;

private:
  RC main_next(); // 主查询遍历下一条数据
  RC sub_next(); // 子查询遍历下一条数据

private:
  Trx *                       trx_        = nullptr;
  PhysicalOperator *          main_oper_  = nullptr;
  PhysicalOperator *          sub_oper_   = nullptr;
  Tuple *                     main_tuple_ = nullptr;
  Tuple *                     sub_tuple_  = nullptr;
  std::unique_ptr<Expression> expression_;
  CompOp                      comp_;
  std::vector<Value>          values_;
  int                         left_is_expr_;
  bool                        round_done_ = true;  // 子查询查完一遍
  bool                        sub_closed_ = true;  // 子查询是否已经关闭
  bool                        ok_         = false;
};