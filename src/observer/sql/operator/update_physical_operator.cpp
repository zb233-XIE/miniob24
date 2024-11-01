#include "sql/operator/update_physical_operator.h"
#include "event/sql_debug.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx) {
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    sql_debug("update got a tuple: %s", tuple->to_string().c_str());

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    records_.emplace_back(std::move(record));
  }

  child->close();

  if (!records_.empty() && update_internal_error_) {
    return RC::INVALID_ARGUMENT;
  }

  for (Record &record: records_) {
    char *updated_data = new char[record.len()];
    memcpy(updated_data, record.data(), record.len());

    for (size_t i = 0; i < fields_.size(); i++) {
      if (values_[i].get_null()) {
        *(int8_t *)(updated_data + fields_[i].offset()) = NULL_MAGIC_NUMBER;
        continue;
      }
      
      const FieldMeta &field = fields_[i];
      if (field.type() == AttrType::CHARS) {
        memset(updated_data + field.offset(), 0, field.len());
      }
      memcpy(updated_data + field.offset(), values_[i].data(), values_[i].length());
    }

    rc = trx->update_record(table_, record, updated_data);
    delete [] updated_data;

    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::SUCCESS;
}
RC UpdatePhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  return RC::SUCCESS;
}
