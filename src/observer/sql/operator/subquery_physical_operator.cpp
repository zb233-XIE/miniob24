#include "sql/operator/subquery_physical_operator.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "storage/trx/trx.h"
#include <cstring>

using namespace std;

SubqueryPhysicalOperator::SubqueryPhysicalOperator(std::unique_ptr<Expression> expression, CompOp comp, int left_is_expr)
    : expression_(std::move(expression)), comp_(comp), left_is_expr_(left_is_expr)
{
}

RC SubqueryPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 2 && values_.empty()) {
    LOG_WARN("subquery operator should have 2 children");
    return RC::INTERNAL;
  }

  RC rc = RC::SUCCESS;

  if (children_.size() > 1) {
    // 主查询是第0个，子查询是第1个
    main_oper_ = children_[1].get();
    sub_oper_  = children_[0].get();
  } else {
    // 这种情况下只有主查询
    main_oper_ = children_[0].get();
  }
  rc = main_oper_->open(trx);
  trx_ = trx;
  return rc;
}

RC SubqueryPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  ok_ = false;

  while (RC::SUCCESS == (rc = main_next())) {
    // 下放刚刚得到的tuple，因为子查询可能会用到该tuple中的内容

    bool in = false;
    bool not_in = true;
    bool exists = false;
    bool not_exists = true;

    Value expr_value, subquery_value;
    int   comp_res;

    if (children_.size() == 1) {
      expression_->get_value(*main_tuple_, expr_value);
      for (auto &v : values_) {
        if (left_is_expr_) {
          comp_res = expr_value.compare(v);
        } else {
          comp_res = v.compare(expr_value);
        }
        if (comp_res == 0) {
          in     = true;
          not_in = false;
        }
      }
      if ((comp_ == CompOp::IN && in) || (comp_ == CompOp::NOT_IN && not_in)) {
        return rc;
      }
      continue;
    }

    // 子查询
    RC rc_sub = RC::SUCCESS;
    rc_sub = sub_oper_->open(trx_);
    if (rc_sub != RC::SUCCESS) {
      LOG_WARN("failed to open sub operator");
      return rc_sub;
    }
    while (OB_SUCC(rc_sub = sub_next())) {
      exists = true;
      not_exists = false;

      expression_->get_value(*main_tuple_, expr_value);
      sub_tuple_->cell_at(0, subquery_value);
      if (left_is_expr_) {
        comp_res = expr_value.compare(subquery_value);
      } else {
        comp_res = subquery_value.compare(expr_value);
      }

      if (comp_res == 0) {
        in = true;
        not_in = false;
        ok_ = (comp_ == CompOp::EQUAL_TO || comp_ == CompOp::LESS_EQUAL || comp_ == CompOp::GREAT_EQUAL);
      } else {
        if (comp_res > 0) {
          ok_ = (comp_ == CompOp::NOT_EQUAL || comp_ == CompOp::GREAT_EQUAL || comp_ == CompOp::GREAT_THAN);
        } else {
          ok_ = (comp_ == CompOp::NOT_EQUAL || comp_ == CompOp::LESS_EQUAL || comp_ == CompOp::LESS_THAN);
        }
      }
    }
    rc_sub = sub_oper_->close();
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to close sub oper. rc=%s", strrc(rc));
    }
    if ((comp_ == CompOp::IN && in) || (comp_ == CompOp::NOT_IN && not_in) || (comp_ == CompOp::EXISTS && exists) ||
        (comp_ == CompOp::NOT_EXISTS && not_exists) || ok_) {
      return rc;
    }
  }
  
  return rc;
}

RC SubqueryPhysicalOperator::close()
{
  RC rc = main_oper_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("falied to close main oper, rc=%s", strrc(rc));
  }
  return rc;
}

Tuple *SubqueryPhysicalOperator::current_tuple()
{
  return main_tuple_;
}

// RC SubqueryPhysicalOperator::tuple_schema(TupleSchema &schema) const
// {
//   return RC::SUCCESS;
// }

RC SubqueryPhysicalOperator::main_next()
{
  RC rc = RC::SUCCESS;
  rc = main_oper_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  main_tuple_ = main_oper_->current_tuple();
  return rc;
}

RC SubqueryPhysicalOperator::sub_next()
{

  RC rc = RC::SUCCESS;
  rc = sub_oper_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  sub_tuple_ = sub_oper_->current_tuple();
  return rc;
}