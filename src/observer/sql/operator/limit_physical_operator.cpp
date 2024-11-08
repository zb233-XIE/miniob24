#include "sql/operator/limit_physical_operator.h"
#include "common/rc.h"

RC LimitPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  rc = children_[0]->open(trx);
  if(rc != RC::SUCCESS){
    LOG_WARN("failed to open child operator. rc=%s", strrc(rc));
  }
  return rc;
}

RC LimitPhysicalOperator::next()
{
  if(children_.empty()){
    return RC::RECORD_EOF;
  }
  if(limits_ <= 0){
    return RC::RECORD_EOF;
  }
  limits_--;
 
  return children_[0]->next();
}

Tuple *LimitPhysicalOperator::current_tuple()
{
  if(limits_ < 0){
    return nullptr;
  }
  return children_[0]->current_tuple();
}

RC LimitPhysicalOperator::close()
{
  RC rc = children_[0]->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close child operator. rc=%s", strrc(rc));
  }
  return rc;
}