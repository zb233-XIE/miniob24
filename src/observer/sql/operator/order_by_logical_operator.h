#include "sql/operator/logical_operator.h"



class OrderByLogicalOperator : public LogicalOperator {
public:
  OrderByLogicalOperator(const std::vector<OrderByItem> &items) : items_(items) {};
  ~OrderByLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::ORDER_BY; }
  const std::vector<OrderByItem> &items() const { return items_; }

private:
  std::vector<OrderByItem> items_;
};