#pragma once

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

private:
  int limits_ [[maybe_unused]];
};