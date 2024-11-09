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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field_meta.h"
#include "storage/index/index.h"
#include "storage/table/table_meta.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString FIELD_UNIQUE("unique");
const static Json::StaticString FIELD_ALGORITHM("distance_algorithm");
const static Json::StaticString FIELD_CENTROIDS("centroids");
const static Json::StaticString FIELD_PROBES("probes");

RC IndexMeta::init(const char *name, const std::vector<FieldMeta> &field_metas, bool unique,
    DISTANCE_ALGO distance_algorithm, int centroids, int probes)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_               = name;
  unique_             = unique;
  distance_algorithm_ = distance_algorithm;
  centroids_          = centroids;
  probes_             = probes;
  for (const FieldMeta &field : field_metas) {
    fields_.push_back(field.name());
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME]       = name_;
  json_value[FIELD_FIELD_NAME] = Json::Value(Json::arrayValue);
  for (const auto &field : fields_) {
    json_value[FIELD_FIELD_NAME].append(field);
  }
  json_value[FIELD_UNIQUE]    = unique_;
  json_value[FIELD_ALGORITHM] = static_cast<int>(distance_algorithm_);
  json_value[FIELD_CENTROIDS] = centroids_;
  json_value[FIELD_PROBES] = probes_;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value      = json_value[FIELD_NAME];
  const Json::Value &fields_value    = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique_value    = json_value[FIELD_UNIQUE];
  const Json::Value &algorithm_value = json_value[FIELD_ALGORITHM];
  const Json::Value &centroids_value = json_value[FIELD_CENTROIDS];
  const Json::Value &probes_value = json_value[FIELD_PROBES];

  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!fields_value.isArray()) {
    LOG_ERROR("Field names of index [%s] are not an array. json value=%s",
        name_value.asCString(), fields_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!unique_value.isBool()) {
    LOG_ERROR("Unique flag of index [%s] is not a boolean. json value=%s",
        name_value.asCString(), unique_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!algorithm_value.isInt()) {
    LOG_ERROR("Distance algorithm flag of vector index [%s] is not an integer. json value=%s",
        name_value.asCString(), algorithm_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!centroids_value.isInt()) {
    LOG_ERROR("Centroids of vector index [%s] is not an integer. json value=%s",
        name_value.asCString(), centroids_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!probes_value.isInt()) {
    LOG_ERROR("Distance algorithm flag of index [%s] is not an integer. json value=%s",
        name_value.asCString(), probes_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  std::vector<FieldMeta> field_metas;
  for (const auto &field_value : fields_value) {
    if (!field_value.isString()) {
      LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
          name_value.asCString(), field_value.toStyledString().c_str());
      return RC::INTERNAL;
    }

    const FieldMeta *field = table.field(field_value.asCString());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_metas.push_back(*field);
  }

  return index.init(
      name_value.asCString(), 
      field_metas, 
      unique_value.asBool(),
      static_cast<DISTANCE_ALGO>(algorithm_value.asInt()),
      centroids_value.asInt(),
      probes_value.asInt());
}

const char *IndexMeta::name() const { return name_.c_str(); }

const std::vector<string> IndexMeta::fields() const { return fields_; }

bool IndexMeta::unique() const { return unique_; }

DISTANCE_ALGO IndexMeta::alrgorithm() const { return distance_algorithm_; }

int IndexMeta::centroids() const { return centroids_; }
int IndexMeta::probes() const { return probes_; }

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", fields=[";
  for (size_t i = 0; i < fields_.size(); ++i) {
    os << fields_[i];
    if (i != fields_.size() - 1) {
      os << ", ";
    }
  }
  os << "]";
}
