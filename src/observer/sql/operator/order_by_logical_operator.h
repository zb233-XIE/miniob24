#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

class OrderByLogicalOperator : public LogicalOperator
{
public:
  OrderByLogicalOperator(const std::vector<OrderByItem> &items) : items_(items){};
  OrderByLogicalOperator(Value &&feature_vector, DISTANCE_ALGO distance_algorithm, string query_field_name)
      : feature_vector_(feature_vector), distance_algorithm_(distance_algorithm), query_fielf_name_(query_field_name)
  {
    vector_order_by_ = true;
  };
  ~OrderByLogicalOperator() = default;

  LogicalOperatorType             type() const override { return LogicalOperatorType::ORDER_BY; }
  const std::vector<OrderByItem> &items() const { return items_; }

  bool          is_vector_order_by() const { return vector_order_by_; }
  Value        &feature_vector() { return feature_vector_; }
  DISTANCE_ALGO distance_algorithm() const { return distance_algorithm_; }
  const string &vector_query_field() const { return query_fielf_name_; }

private:
  std::vector<OrderByItem> items_;

  bool vector_order_by_ = false;
  // variables below are for vector order by = true
  Value         feature_vector_;
  DISTANCE_ALGO distance_algorithm_ = DISTANCE_ALGO::NONE;
  string        query_fielf_name_;
};