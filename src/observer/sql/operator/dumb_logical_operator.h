#pragma once

#include "sql/operator/logical_operator.h"

class DumbLogicalOperator : public LogicalOperator
{
public:
  LogicalOperatorType type() const override { return LogicalOperatorType::DUMB; }
  
private:

};