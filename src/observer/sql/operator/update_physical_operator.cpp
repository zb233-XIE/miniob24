#include "sql/operator/update_physical_operator.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/record/record.h"
#include "event/sql_debug.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  std::vector<std::string> real_field_names;
  std::vector<FieldMeta> real_fields;
  bool has_view = false;
  if (table_->view()) {
    has_view = true;
    View *view = table_->view();
    for (const FieldMeta &field : fields_) {
      std::string real_field_name;
      table_->view()->col_to_field_lookup(field.name(), real_field_name);
      real_field_names.push_back(real_field_name);
    }

    table_ = view->handle_view_update(real_field_names, real_fields);
    if (table_ == nullptr) {
      LOG_WARN("failed to handle view update");
      return RC::INTERNAL;
    }
  }

  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    sql_debug("update got a tuple: %s", tuple->to_string().c_str());

    if (has_view) {
      ValueListTuple *val_list_tuple = static_cast<ValueListTuple *>(tuple);
      if (val_list_tuple->is_record_set()) {
        Record record = val_list_tuple->record();
        records_.emplace_back(std::move(record));
      } else if (val_list_tuple->is_joined_map_set()) {
        Record record;
        val_list_tuple->lookup_joined_map(table_->name(), record);
        records_.emplace_back(record);
      } else {
        return RC::INVALID_ARGUMENT;
      }
    } else {
      RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
      Record   &record    = row_tuple->record();
      records_.emplace_back(std::move(record));
    }
  }

  child->close();

  if (!records_.empty() && update_internal_error_) {
    return RC::INVALID_ARGUMENT;
  }

  bool contain_lob_field = table_->table_meta().contain_lob_field();

  for (Record &record : records_) {
    if (contain_lob_field) {
      // in-place update
      // decompose then reassemble
      const int     normal_field_start_index = table_->table_meta().sys_field_num();
      int           field_count              = table_->table_meta().field_num() - normal_field_start_index;
      vector<Value> updated_values(field_count);
      Record        updated_record;
      for (int i = 0; i < field_count; i++) {
        const FieldMeta *out_field        = table_->table_meta().out_field(i + normal_field_start_index);
        int              out_field_len    = out_field->len();
        int              out_field_offset = out_field->offset();
        updated_values[i].set_type(out_field->type());
        updated_values[i].set_data(record.data() + out_field_offset, out_field_len);
      }
      for (size_t i = 0; i < fields_.size(); i++) {
        const auto& field = fields_[i];
        int idx = field.field_id();
        updated_values[idx].set_data(values_[i].data(), values_[i].length());
      }

      // split record into: record + record_lob_anno
      rc = table_->make_record(field_count, updated_values.data(), updated_record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to make record. rc=%s", strrc(rc));
        return rc;
      }

      Record_LOB_ANNO record_lob_anno;
      rc = table_->make_record_lob_anno(field_count, updated_values.data(), record_lob_anno);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to make record LOB annotations. rc=%s", strrc(rc));
        return rc;
      }
      rc = trx->update_record(table_, record, updated_record, record_lob_anno.data());
    } else {
      char *updated_data = nullptr;
      updated_data       = new char[record.len()];
      memcpy(updated_data, record.data(), record.len());
      int field_count = has_view ? real_fields.size() : fields_.size();

    for (size_t i = 0; i < field_count; i++) {
      const FieldMeta &field = has_view ? real_fields[i] : fields_[i];
      if (values_[i].get_null()) {
        if (fields_[i].type() == AttrType::CHARS) {
          *(uint8_t *)(updated_data + fields_[i].offset()) = NULL_CHAR_MAGIC_NUMBER;
        } else {
          *(uint32_t *)(updated_data + fields_[i].offset()) = NULL_INT_MAGIC_NUMER;
        }
        continue;
      }
      
      if (field.type() == AttrType::CHARS) {
        memset(updated_data + field.offset(), 0, field.len());
      }
      memcpy(updated_data + field.offset(), values_[i].data(), values_[i].length());
    }

      rc = trx->update_record(table_, record, updated_data);
      delete[] updated_data;
    }
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::SUCCESS;
}
RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }
