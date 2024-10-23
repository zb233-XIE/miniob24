#pragma once

#include "sql/operator/logical_operator.h"

class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, const FieldMeta &field, Value *value);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }
  Table              *table() const { return table_; }
  Value              *value() const { return value_; }
  const FieldMeta    &field() const { return field_; }

private:
  Table    *table_ = nullptr;
  FieldMeta field_;
  Value    *value_;
};