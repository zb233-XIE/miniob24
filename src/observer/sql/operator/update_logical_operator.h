#pragma once

#include "sql/operator/logical_operator.h"

class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, const std::vector<Value> &values, const std::vector<FieldMeta> &fields, bool subq_multi_results_flag);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }
  Table              *table() const { return table_; }
  const std::vector<Value> &values() const { return values_; }
  const std::vector<FieldMeta> &fields() const { return fields_; }
  const bool subq_multi_results_flag() const { return subq_multi_results_flag_; }

private:
  Table    *table_ = nullptr;
  std::vector<FieldMeta> fields_;
  std::vector<Value> values_;
  bool subq_multi_results_flag_ = false;
};