#include "sql/expr/expression_tuple.h"
#include "sql/operator/physical_operator.h"

class ViewGetPhysicalOperator: public PhysicalOperator {
public:
  ViewGetPhysicalOperator() {};
  ~ViewGetPhysicalOperator() {};

  PhysicalOperatorType type() const override { return PhysicalOperatorType::VIEW_GET; }
  RC open(Trx *trx) override;
  RC close() override;
  RC next() override;
  Tuple *current_tuple() override;
  RC tuple_schema(TupleSchema &schema) const override;

private:
  ValueListTuple tuple_;
};
