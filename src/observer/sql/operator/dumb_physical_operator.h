#pragma once

#include "sql/operator/physical_operator.h"

class DumbPhysicalOperator : public PhysicalOperator
{
public:
  PhysicalOperatorType type() const override { return PhysicalOperatorType::DUMB; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

private:
};