#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"

class LimitPhysicalOperator : public PhysicalOperator
{
public:
  LimitPhysicalOperator(int limits): limits_(limits) {}
  virtual ~LimitPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::LIMIT; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Tuple* current_tuple() override;

private:
  int limits_;
};