#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const std::vector<Value> &values, const std::vector<FieldMeta> &fields, bool update_internal_error)
    : table_(table), fields_(fields), values_(values), update_internal_error_(update_internal_error)
{}
