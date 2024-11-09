/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "sql/parser/parse_defs.h"
#include "storage/index/index.h"
#include "storage/index/kmeans.h"
#include "storage/record/record.h"
#include <utility>
#include <vector>

/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */
class IvfflatIndex : public Index
{
public:
  using IndexKV     = std::pair<Value, RID>;
  using SortItem    = std::pair<float, int>;  // <distance, index>
  using OrderByFunc = std::function<RC(const Value &, const Value &, Value &)>;
  IvfflatIndex()    = default;
  virtual ~IvfflatIndex() noexcept {};

  RC create(Table *table, const char *file_name, const IndexMeta &index_meta,
      const std::vector<FieldMeta> &field_metas) override
  {
    return RC::UNSUPPORTED;
  }
  RC create(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta);

  RC open(Table *table, const char *file_name, const IndexMeta &index_meta,
      const std::vector<FieldMeta> &field_metas) override
  {
    return RC::UNSUPPORTED;
  }
  RC open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
  {
    return RC::UNIMPLEMENTED;
  };

  vector<RID> ann_search(const Value &base_vector, size_t limit);

  RC close() { return RC::UNIMPLEMENTED; }

  void generate();
  void setup();
  RC   insert_entry(const char *record, const RID *rid) override;
  RC   delete_entry(const char *record, const RID *rid) override { return RC::UNIMPLEMENTED; };

  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
      int right_len, bool right_inclusive) override
  {
    return nullptr;
  }
  RC sync() override { return RC::UNIMPLEMENTED; };

private:
  bool                 inited_                  = false;
  Table               *table_                   = nullptr;
  int                  lists_                   = 1;
  int                  probes_ [[maybe_unused]] = 1;
  DISTANCE_ALGO        algorithm_               = DISTANCE_ALGO::NONE;
  Kmeans              *kmeans_                  = nullptr;
  std::vector<IndexKV> index_entries_;
  // the center vector of each cluster
  vector<Value> centers_;
  // vectors each cluster contains
  // indexes in each cluster is used to index into index_entries
  vector<vector<int>> cluster_;
  OrderByFunc         calc_dis_ = nullptr;
};
