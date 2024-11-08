#include "common/log/log.h"
#include "common/type/attr_type.h"
#include "common/value.h"
#include "sql/expr/expression.h"
#include "sql/expr/expression_tuple.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include <functional>
#include <memory>
#include <vector>

using OrderByTuple      = std::vector<Value>;
using VectorOrderByFunc = std::function<RC(const Value &, const Value &, Value &)>;

class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator(const std::vector<OrderByItem> &items) : items_(items){};
  OrderByPhysicalOperator(Value &&feature_vector, string query_field_name, DISTANCE_ALGO distance_algorithm)
      : feature_vector_(feature_vector), query_field_name_(query_field_name)
  {
    vector_order_by_ = true;
    switch (distance_algorithm) {
      case DISTANCE_ALGO::COSINE_DISTANCE: {
        calc_distance_ = &Value::cosine_distance;
      } break;
      case DISTANCE_ALGO::L2_DISTANCE: {
        calc_distance_ = &Value::l2_distance;
      } break;
      case DISTANCE_ALGO::INNER_PRODUCT: {
        calc_distance_ = &Value::inner_product;
      } break;
      default: {
        LOG_WARN("vector order by invalid distance algorithm");
      }
    }
  }
  ~OrderByPhysicalOperator();

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }
  RC                   open(Trx *trx) override;
  RC                   close() override;
  RC                   next() override;
  Tuple               *current_tuple() override;
  RC                   tuple_schema(TupleSchema &schema) const override { return children_[0]->tuple_schema(schema); }

  RC sort();
  RC vector_sort();

private:
  bool                      sorted_ = false;
  int                       cur_idx = -1;
  std::vector<OrderByItem>  items_;
  std::vector<int>          item_indexes_;
  std::vector<OrderByTuple> sorted_tuples_;
  ValueListTuple            current_tuple_;

  // order by operations on vector type
  bool              vector_order_by_ = false;
  Value             feature_vector_;
  VectorOrderByFunc calc_distance_ = nullptr;
  string            query_field_name_;
  int               query_cell_index = -1;

  struct VectorOrderByTuple
  {
    vector<Value> value;
    float         distance;
    bool          operator<(const VectorOrderByTuple &rhs) const { return this->distance < rhs.distance; }
    bool          operator>(const VectorOrderByTuple &rhs) const { return this->distance > rhs.distance; }
    bool          operator==(const VectorOrderByTuple &rhs) const { return this->distance == rhs.distance; }
  };
  std::vector<VectorOrderByTuple> vector_sorted_tuples_;
};