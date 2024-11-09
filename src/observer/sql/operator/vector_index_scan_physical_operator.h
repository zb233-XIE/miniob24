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

#pragma once

#include "common/type/vector_type.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/index/index.h"
#include "storage/record/record_manager.h"

/**
 * @brief 索引扫描物理算子
 * @ingroup PhysicalOperator
 */
class VectorIndexScanPhysicalOperator : public PhysicalOperator
{
public:
  VectorIndexScanPhysicalOperator(Table *table, Index *index, ReadWriteMode mode, Value &&feature_vector, int limits);

  virtual ~VectorIndexScanPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::VECTOR_INDEX_SCAN; }

  std::string param() const override;

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  // 与TableScanPhysicalOperator代码相同，可以优化
  RC filter(RowTuple &tuple, bool &result);

private:
  Trx               *trx_            = nullptr;
  Table             *table_          = nullptr;
  Index             *index_          = nullptr;
  ReadWriteMode      mode_           = ReadWriteMode::READ_WRITE;
  RecordFileHandler *record_handler_ = nullptr;

  Record      current_record_;
  RowTuple    tuple_;
  Value       feature_vector_;
  int         limits_;
  bool        ann_searched_ = false;
  int         cur_index_    = -1;
  vector<RID> record_rids_;
};
