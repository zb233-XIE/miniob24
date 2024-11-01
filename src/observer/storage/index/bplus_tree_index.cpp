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

#include "storage/index/bplus_tree_index.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "storage/table/table.h"
#include "storage/db/db.h"

BplusTreeIndex::~BplusTreeIndex() noexcept { close(); }

RC BplusTreeIndex::create(Table *table, const char *file_name, const IndexMeta &index_meta, const std::vector<FieldMeta> &field_metas)
{
  if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s, field:%s",
        file_name, index_meta.name(), FieldMeta::attrs_to_str(index_meta.fields()).c_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas);

  std::vector<AttrType> types;
  std::vector<int> lens;
  for (size_t i = 0; i < field_metas.size(); ++i) {
    types.push_back(field_metas[i].type());
    lens.push_back(field_metas[i].len());
  }

  BufferPoolManager &bpm = table->db()->buffer_pool_manager();
  RC rc = index_handler_.create(table->db()->log_handler(), bpm, file_name, types, lens);
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, field:%s, rc:%s",
        file_name, index_meta.name(), FieldMeta::attrs_to_str(index_meta.fields()).c_str(), strrc(rc));
    return rc;
  }

  inited_ = true;
  table_  = table;
  LOG_INFO("Successfully create index, file_name:%s, index:%s, field:%s",
    file_name, index_meta.name(), FieldMeta::attrs_to_str(index_meta.fields()).c_str());
  return RC::SUCCESS;
}

RC BplusTreeIndex::open(Table *table, const char *file_name, const IndexMeta &index_meta, const std::vector<FieldMeta> &field_metas)
{
  if (inited_) {
    LOG_WARN("Failed to open index due to the index has been initedd before. file_name:%s, index:%s, field:%s",
        file_name, index_meta.name(), FieldMeta::attrs_to_str(index_meta.fields()).c_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, field_metas);

  BufferPoolManager &bpm = table->db()->buffer_pool_manager();
  RC rc = index_handler_.open(table->db()->log_handler(), bpm, file_name);
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to open index_handler, file_name:%s, index:%s, field:%s, rc:%s",
        file_name, index_meta.name(), FieldMeta::attrs_to_str(index_meta.fields()).c_str(), strrc(rc));
    return rc;
  }

  inited_ = true;
  table_  = table;
  LOG_INFO("Successfully open index, file_name:%s, index:%s, field:%s",
    file_name, index_meta.name(), FieldMeta::attrs_to_str(index_meta.fields()).c_str());
  return RC::SUCCESS;
}

RC BplusTreeIndex::close()
{
  if (inited_) {
    LOG_INFO("Begin to close index, index:%s, field:%s", index_meta_.name(), FieldMeta::attrs_to_str(index_meta_.fields()).c_str());
    index_handler_.close();
    inited_ = false;
  }
  LOG_INFO("Successfully close index.");
  return RC::SUCCESS;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid)
{ 
  sql_debug("table_name:%s;index_name:%s; fields: %s\n", table_->name(), index_meta_.name(), FieldMeta::attrs_to_str(index_meta_.fields()).c_str());
  bool has_null = false;
  const char *key = make_key(record, has_null);
  int key_len = index_handler_.file_header().total_attr_length;

  if (index_meta_.unique()) {
    std::list<RID> rids;
    index_handler_.get_entry(key, key_len, rids);
    if (rids.size() > 0 && !has_null) {
      LOG_WARN("Failed to insert entry due to the key is already existed. key:%s", key);
      delete [] key;
      return RC::RECORD_DUPLICATE_KEY;
    }
  }

  RC rc = index_handler_.insert_entry(key, rid);
  delete [] key;
  return rc;
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid)
{
  bool has_null = false;
  const char *key = make_key(record, has_null);
  RC rc = index_handler_.delete_entry(key, rid);
  delete [] key;
  return rc;
}

IndexScanner *BplusTreeIndex::create_scanner(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(index_handler_);
  RC rc = index_scanner->open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete index_scanner;
    return nullptr;
  }
  return index_scanner;
}

RC BplusTreeIndex::sync() { return index_handler_.sync(); }

const char *BplusTreeIndex::make_key(const char *record, bool &has_null)
{
  int key_len = index_handler_.file_header().total_attr_length;
  char *key = new char[key_len + sizeof(RID)];
  char *pkey = key;
  for (size_t i = 0; i < field_metas_.size(); ++i) {
    if (*(uint8_t *)(record + field_metas_[i].offset()) == NULL_MAGIC_NUMBER) {
      has_null = true;
    }
    memcpy(pkey, record + field_metas_[i].offset(), field_metas_[i].len());
    pkey += field_metas_[i].len();
  }
  memset(key + key_len, 0, sizeof(RID));
  return key;
}

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeHandler &tree_handler) : tree_scanner_(tree_handler) {}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept { tree_scanner_.close(); }

RC BplusTreeIndexScanner::open(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  return tree_scanner_.open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
}

RC BplusTreeIndexScanner::next_entry(RID *rid) { return tree_scanner_.next_entry(*rid); }

RC BplusTreeIndexScanner::destroy()
{
  delete this;
  return RC::SUCCESS;
}
