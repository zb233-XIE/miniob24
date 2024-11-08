#include "sql/operator/limit_physical_operator.h"

RC LimitPhysicalOperator::open(Trx *trx)
{
  return RC::SUCCESS;
}

RC LimitPhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC LimitPhysicalOperator::close()
{
  return RC::SUCCESS;
}