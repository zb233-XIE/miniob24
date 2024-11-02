#include "sql/expr/expression_tuple.h"
#include "sql/operator/physical_operator.h"

typedef std::vector<Value> OrderByTuple;

class OrderByPhysicalOperator: public PhysicalOperator {
public:
  OrderByPhysicalOperator(const std::vector<OrderByItem> &items) : items_(items) {};
  ~OrderByPhysicalOperator();

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }
  RC open(Trx *trx) override;
  RC close() override;
  RC next() override;
  Tuple *current_tuple() override;
  RC tuple_schema(TupleSchema &schema) const override { return children_[0]->tuple_schema(schema); }

  RC sort();
private:
  bool sorted_ = false;
  int cur_idx = -1;
  std::vector<OrderByItem> items_;
  std::vector<int> item_indexes_;
  std::vector<OrderByTuple> sorted_tuples_;
  ValueListTuple current_tuple_;
};