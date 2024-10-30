#pragma once

#include "sql/operator/physical_operator.h"

class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, const std::vector<Value> &values, const std::vector<FieldMeta> &fields, bool subq_multi_results_flag)
      : table_(table), values_(values), fields_(fields), subq_multi_results_flag_(subq_multi_results_flag)
  {}
  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table              *table_ = nullptr;
  std::vector<Value> values_;
  std::vector<FieldMeta> fields_;
  std::vector<Record> records_;
  bool subq_multi_results_flag_ = false;
};
