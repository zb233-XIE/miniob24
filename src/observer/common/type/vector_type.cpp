/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/type/attr_type.h"
#include "common/type/vector_type.h"
#include "common/value.h"
#include "common/lang/limits.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <vector>

int VectorType::compare(const Value &left, const Value &right) const
{
  std::vector<float> *left_val = left.get_vector();
  std::vector<float> *right_val = right.get_vector();
  ASSERT(left_val != nullptr, "left type is not vector");
  ASSERT(right_val != nullptr, "right type is not vector");
  int flag = common::compare_vector((void *)(left_val->data()), left_val->size(),
                                    (void *)(right_val->data()), right_val->size());
  delete left_val;
  delete right_val;
  return flag;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const
{
  std::vector<float> *left_val = left.get_vector();
  std::vector<float> *right_val = right.get_vector();
  ASSERT(left_val != nullptr, "left type is not vector");
  ASSERT(right_val != nullptr, "right type is not vector");
  if(left_val->size() != right_val->size()){
    LOG_WARN("VEC_ADD Dimension mismatch");
    return RC::UNSUPPORTED;
  }
  vector<float> result_vec(left_val->size());
  std::transform(left_val->begin(), left_val->end(),
                right_val->begin(), result_vec.begin(),
                [](float a, float b){return a+b;});
  result.set_vector(result_vec.data(), result_vec.size());
  delete left_val;
  delete right_val;
  return RC::SUCCESS;
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const
{
  std::vector<float> *left_val  = left.get_vector();
  std::vector<float> *right_val = right.get_vector();
  ASSERT(left_val != nullptr, "left type is not vector");
  ASSERT(right_val != nullptr, "right type is not vector");
  if (left_val->size() != right_val->size()) {
    LOG_WARN("VEC_SUB Dimension mismatch");
    return RC::UNSUPPORTED;
  }
  vector<float> result_vec(left_val->size());
  std::transform(left_val->begin(), left_val->end(), right_val->begin(), result_vec.begin(), [](float a, float b) {
    return a - b;
  });
  result.set_vector(result_vec.data(), result_vec.size());
  delete left_val;
  delete right_val;
  return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const
{
  std::vector<float> *left_val  = left.get_vector();
  std::vector<float> *right_val = right.get_vector();
  ASSERT(left_val != nullptr, "left type is not vector");
  ASSERT(right_val != nullptr, "right type is not vector");
  if (left_val->size() != right_val->size()) {
    LOG_WARN("VEC_MULT Dimension mismatch");
    return RC::UNSUPPORTED;
  }
  vector<float> result_vec(left_val->size());
  std::transform(left_val->begin(), left_val->end(), right_val->begin(), result_vec.begin(), [](float a, float b) {
    return a * b;
  });
  result.set_vector(result_vec.data(), result_vec.size());
  delete left_val;
  delete right_val;
  return RC::SUCCESS;
}

RC VectorType::l2_distance(const Value &left, const Value &right, Value &result) const{
  std::vector<float> *left_val  = left.get_vector();
  std::vector<float> *right_val = right.get_vector();
  ASSERT(left_val != nullptr, "left type is not vector");
  ASSERT(right_val != nullptr, "right type is not vector");
  if (left_val->size() != right_val->size()) {
    LOG_WARN("Vector Dimension mismatch");
    return RC::UNSUPPORTED;
  }
  float product_sum = std::inner_product(left_val->begin(), left_val->end(), right_val->begin(), 0.0,
                                        std::plus<double>{},
                                        [](double a, double b){
                                          return (a-b) * (a-b);
                                        });
  result.set_float(std::sqrt(product_sum));
  return RC::SUCCESS;
}

RC VectorType::inner_product(const Value &left, const Value &right, Value &result) const{
  std::vector<float> *left_val  = left.get_vector();
  std::vector<float> *right_val = right.get_vector();
  ASSERT(left_val != nullptr, "left type is not vector");
  ASSERT(right_val != nullptr, "right type is not vector");
  if (left_val->size() != right_val->size()) {
    LOG_WARN("VEC_MULT Dimension mismatch");
    return RC::UNSUPPORTED;
  }
  float inner_product = std::inner_product(left_val->begin(), left_val->end(), right_val->begin(), 0.0);
  result.set_float(inner_product);
  return RC::SUCCESS;
}

RC VectorType::cosine_distance(const Value &left, const Value &right, Value &result) const{
  std::vector<float> *left_val  = left.get_vector();
  std::vector<float> *right_val = right.get_vector();
  ASSERT(left_val != nullptr, "left type is not vector");
  ASSERT(right_val != nullptr, "right type is not vector");
  if (left_val->size() != right_val->size()) {
    LOG_WARN("Vector Dimension mismatch");
    return RC::UNSUPPORTED;
  }
  float mag_left = std::sqrt(std::accumulate(left_val->begin(), left_val->end(), 0.0, 
            [](double sum, double i){
              return sum + i * i;
            }));
  float mag_right = std::sqrt(std::accumulate(right_val->begin(), right_val->end(), 0.0, 
            [](double sum, double i){
              return sum + i * i;
            }));
  float inner_product = std::inner_product(left_val->begin(), left_val->end(), right_val->begin(), 0.0);
  float cos_distance = 1.0 - inner_product / (mag_left * mag_right);
  result.set_float(cos_distance);
  return RC::SUCCESS;
}

RC VectorType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << "[";
  string str;
  for(int i=0; i < val.length(); i++){
    if(i) ss << ", ";
    ss << common::double_to_str(*(val.value_.vector_value_ + i));
  }
  ss << "]";
  result = ss.str();
  return RC::SUCCESS;
}