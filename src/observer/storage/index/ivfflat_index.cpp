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
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "common/value.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field_meta.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "storage/index/index.h"
#include "storage/index/ivfflat_index.h"
#include "storage/index/kmeans.h"
#include "storage/table/table.h"
#include "storage/db/db.h"
#include <algorithm>
#include <list>
#include <vector>

// BplusTreeIndex::~BplusTreeIndex() noexcept { close(); }

RC IvfflatIndex::create(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
{
  if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s, field:%s",
        file_name, index_meta.name(), FieldMeta::attrs_to_str(index_meta.fields()).c_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, std::vector<FieldMeta>{field_meta});

  inited_    = true;
  table_     = table;
  lists_     = index_meta.centroids();
  probes_    = index_meta.probes();
  algorithm_ = index_meta.alrgorithm();

  LOG_INFO("Successfully create index, file_name:%s, index:%s, field:%s",
    file_name, index_meta.name(), FieldMeta::attrs_to_str(index_meta.fields()).c_str());
  return RC::SUCCESS;
}

RC IvfflatIndex::insert_entry(const char *record, const RID *rid)
{
  sql_debug("table_name:%s;index_name:%s; fields: %s\n",
      table_->name(),
      index_meta_.name(),
      FieldMeta::attrs_to_str(index_meta_.fields()).c_str());

  int          field_offset = field_metas_[0].offset();
  int          dim          = field_metas_[0].len() / sizeof(float);
  const float *field_base   = reinterpret_cast<const float *>(record + field_offset);
  Value        vector_value(field_base, dim);
  index_entries_.push_back({std::move(vector_value), (*rid)});

  return RC::SUCCESS;
}

void IvfflatIndex::generate()
{
  int dim  = field_metas_[0].len() / sizeof(float);
  int size = index_entries_.size();

  lists_  = std::min(lists_, size);
  probes_ = std::min(probes_, lists_);

  if (kmeans_ == nullptr) {
    kmeans_ = new Kmeans(lists_, size, dim, algorithm_);
  }
  ASSERT(kmeans_ != nullptr, "");

  int index = 0;
  for (const auto &[value, _] : index_entries_) {
    kmeans_->set_data(index, value.data());
    index++;
  }
  ASSERT(index == size, "");
  kmeans_->generate_index();
  setup();
}

void IvfflatIndex::setup()
{
  ASSERT(kmeans_->converge(), "");
  int size = index_entries_.size();
  int dim  = field_metas_[0].len() / sizeof(float);
  // set up center values
  centers_.resize(lists_);
  for (int i = 0; i < lists_; i++) {
    centers_[i] = Value(kmeans_->clusterCenter(i), dim);
  }
  // set up cluster
  cluster_.resize(lists_);
  for (int i = 0; i < size; i++) {
    cluster_[kmeans_->belongToCluster(i)].push_back(i);
  }
  // once set up destroy kmeans to save memory
  delete kmeans_;
}

vector<RID> IvfflatIndex::ann_search(const Value &base_vector, size_t limit)
{
  if (calc_dis_ == nullptr) {
    switch (algorithm_) {
      case DISTANCE_ALGO::COSINE_DISTANCE: {
        calc_dis_ = &Value::cosine_distance;
      } break;
      case DISTANCE_ALGO::L2_DISTANCE: {
        calc_dis_ = &Value::l2_distance;
      } break;
      case DISTANCE_ALGO::INNER_PRODUCT: {
        calc_dis_ = &Value::inner_product;
      } break;
      default: {
        LOG_WARN("vector order by invalid distance algorithm");
        ASSERT(false, "");
      }
    }
  }
  // pick probes_ number of centers closest to base_vector
  vector<SortItem> centerSort;
  Value            distance;
  for (int i = 0; i < lists_; i++) {
    calc_dis_(base_vector, centers_[i], distance);
    centerSort.push_back({distance.get_float(), i});
  }
  std::sort(centerSort.begin(), centerSort.end());
  // do iteration on the cluster[: probes_]
  vector<SortItem> vectorSort;
  for(int i=0; i<probes_; i++){
    auto [_, centerIndex] = centerSort[i];
    for (int vectorIndex : cluster_[centerIndex]) {
      auto &vector_value = index_entries_[vectorIndex].first;
      calc_dis_(base_vector, vector_value, distance);
      vectorSort.push_back({distance.get_float(), vectorIndex});
    }
  }
  
  std::sort(vectorSort.begin(), vectorSort.end());
  // build return vector
  limit = std::min(limit, vectorSort.size());
  vector<RID> ret(limit);
  for (int i = 0; i < limit; i++) {
    int vectorIndex = vectorSort[i].second;
    ret[i] = index_entries_[vectorIndex].second;
  }
  return ret;
}