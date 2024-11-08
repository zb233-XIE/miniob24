#include "sql/operator/logical_operator.h"



class LimitLogicalOperator : public LogicalOperator {
public:
  LimitLogicalOperator(int limits) : limits_(limits) {};
  ~LimitLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::LIMIT; }
  int limits() const { return limits_; }

private:
  int limits_;
};