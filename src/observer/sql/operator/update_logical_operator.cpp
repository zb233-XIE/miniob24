#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const std::vector<Value> &values, const std::vector<FieldMeta> &fields)
    : table_(table), fields_(fields), values_(values)
{}
