#pragma once

#include "sql/operator/physical_operator.h"

class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, Value *value, const FieldMeta &field)
      : table_(table), value_(value), field_(field)
  {}
  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table              *table_ = nullptr;
  Value              *value_ = nullptr;
  FieldMeta           field_;
  std::vector<Record> records_;
};
