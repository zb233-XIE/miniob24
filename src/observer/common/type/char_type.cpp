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
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/type/attr_type.h"
#include "common/type/char_type.h"
#include "common/type/data_type.h"
#include "common/value.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <string>

int CharType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

bool CharType::cast_to_vector(char* src, Value& result) const
{
  int src_len = std::strlen(src);
  if(src[0] == '[' && src[src_len - 1] == ']'){
    src = common::substr(src, 1, src_len-2);
    vector<char*> elems_str;
    common::split_string(src, ',', elems_str, true);
    int len = elems_str.size();
    float* elems = new float[len];
    for(int i=0; i<len; i++){
      char*& elem_str = elems_str[i];
      elem_str = common::strip(elem_str);
      size_t sz = std::strlen(elem_str);
      size_t pos;
      try {
        *(elems + i) = std::stof(elem_str, &pos);
      } catch (const std::invalid_argument& err) {
        LOG_INFO("Invalid input: %s is not a valid float", elem_str);
        delete [] elems;
        return false;
      }
      if(pos != sz){
        LOG_INFO("Invalid input: %s is not a valid float", elem_str);
        delete [] elems;
        return false;
      }
    }
    result.set_vector(elems, len);
    delete [] elems;
    return true;
  }
  return false;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::INTS: {
      int res = atoi(val.get_string().c_str());
      result = Value((int)res);
      break;
    }
    case AttrType::FLOATS: {
      float res = atof(val.get_string().c_str());
      result = Value((float)res);
      break;
    }
    case AttrType::VECTORS: {
      char* src = val.value_.pointer_value_;
      if(cast_to_vector(src, result)){
        return RC::SUCCESS;
      } else {
        LOG_INFO("%s: not a valid string representation of vector", src);
        return RC::INVALID_ARGUMENT;
      }
    } break;
    default: return RC::UNSUPPORTED;
  }
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type)
{
  if (type == AttrType::CHARS) {
    return 0;
  } else if(type == AttrType::VECTORS){
    return 1;
  }
  if (type == AttrType::INTS) { // char转可以转int
    return 0;
  }
  if (type == AttrType::FLOATS) { // char可以转float
    return 0;
  }
  return INT32_MAX;
}

RC CharType::to_string(const Value &val, string &result) const
{
  if (val.get_null()) {
    result = "NULL";
    return RC::SUCCESS;
  }

  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}