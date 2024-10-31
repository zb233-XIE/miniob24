#pragma once

#include "sql/operator/physical_operator.h"

class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, const std::vector<Value> &values, const std::vector<FieldMeta> &fields, bool update_internal_error)
      : table_(table), values_(values), fields_(fields), update_internal_error_(update_internal_error)
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
  bool update_internal_error_ = false;
};
