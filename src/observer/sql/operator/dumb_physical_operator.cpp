#include "sql/operator/dumb_physical_operator.h"

RC DumbPhysicalOperator::open(Trx *trx)
{
  return RC::SUCCESS;
}

RC DumbPhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC DumbPhysicalOperator::close()
{
  return RC::SUCCESS;
}