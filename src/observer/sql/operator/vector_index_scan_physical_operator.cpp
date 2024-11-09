/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/07/08.
//

#include "sql/operator/vector_index_scan_physical_operator.h"
#include "common/rc.h"
#include "common/type/data_type.h"
#include "sql/expr/tuple.h"
#include "storage/index/index.h"
#include "storage/index/ivfflat_index.h"
#include "storage/trx/trx.h"

VectorIndexScanPhysicalOperator::VectorIndexScanPhysicalOperator(
    Table *table, Index *index, ReadWriteMode mode, Value &&feature_vector, int limits)
    : table_(table), index_(index), mode_(mode), feature_vector_(feature_vector), limits_(limits)
{}

RC VectorIndexScanPhysicalOperator::open(Trx *trx)
{
  if (nullptr == table_ || nullptr == index_) {
    return RC::INTERNAL;
  }
  record_handler_ = table_->record_handler();
  if (nullptr == record_handler_) {
    LOG_WARN("invalid record handler");
    return RC::INTERNAL;
  }
  tuple_.set_schema(table_, table_->table_meta().output_field_metas());
  trx_ = trx;
  return RC::SUCCESS;
}

RC VectorIndexScanPhysicalOperator::next()
{
  if (!ann_searched_) {
    record_rids_  = dynamic_cast<IvfflatIndex *>(index_)->ann_search(feature_vector_, limits_);
    ann_searched_ = true;
  }

  if (++cur_index_ >= static_cast<int>(record_rids_.size())) {
    return RC::RECORD_EOF;
  }
  RID current_rid = record_rids_[cur_index_];
  RC  rc          = record_handler_->get_record(current_rid, current_record_);
  if (OB_FAIL(rc)) {
    LOG_TRACE("failed to get record. rid=%s, rc=%s", current_rid.to_string().c_str(), strrc(rc));
    return rc;
  }
  rc = trx_->visit_record(table_, current_record_, mode_);
  if (rc == RC::RECORD_INVISIBLE) {
    LOG_TRACE("record invisible");
  }
  return rc;
}

RC VectorIndexScanPhysicalOperator::close()
{
  return RC::SUCCESS;
}

Tuple *VectorIndexScanPhysicalOperator::current_tuple()
{
  tuple_.set_record(&current_record_);
  return &tuple_;
}

std::string VectorIndexScanPhysicalOperator::param() const
{
  return std::string(index_->index_meta().name()) + " ON " + table_->name();
}
