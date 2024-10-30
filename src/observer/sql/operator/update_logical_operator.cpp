#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const std::vector<Value> &values, const std::vector<FieldMeta> &fields, bool subq_multi_results_flag)
    : table_(table), fields_(fields), values_(values), subq_multi_results_flag_(subq_multi_results_flag)
{}
