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
// Created by Wangyunlai 2023/6/27
//

#pragma once

#include "common/lang/string.h"
#include "common/lang/memory.h"
#include "common/type/attr_type.h"
#include "common/type/data_type.h"
#include <vector>

/**
 * @brief 属性的值
 * @ingroup DataType
 * @details 与DataType，就是数据类型，配套完成各种算术运算、比较、类型转换等操作。这里同时记录了数据的值与类型。
 * 当需要对值做运算时，建议使用类似 Value::add 的操作而不是 DataType::add。在进行运算前，应该设置好结果的类型，
 * 比如进行两个INT类型的除法运算时，结果类型应该设置为FLOAT。
 */
class Value final
{
public:
  friend class DataType;
  friend class IntegerType;
  friend class FloatType;
  friend class BooleanType;
  friend class CharType;
  friend class VectorType;

  Value() = default;

  ~Value() { reset(); }

  Value(AttrType attr_type, char *data, int length = 4) : attr_type_(attr_type) { this->set_data(data, length); }

  explicit Value(int val);
  explicit Value(float val);
  explicit Value(bool val);
  explicit Value(const char *s, int len = 0);
  explicit Value(time_t val);
  explicit Value(const float* base, int len = 0);

  Value(const Value &other);
  Value(Value &&other);

  Value &operator=(const Value &other);
  Value &operator=(Value &&other);

  void reset();

  static RC add(const Value &left, const Value &right, Value &result)
  {
    RC rc = DataType::type_instance(result.attr_type())->add(left, right, result);
    if (left.get_null() || right.get_null()) {
      result.set_null();
    }
    return rc;
  }

  static RC subtract(const Value &left, const Value &right, Value &result)
  {
    RC rc = DataType::type_instance(result.attr_type())->subtract(left, right, result);
    if (left.get_null() || right.get_null()) {
      result.set_null();
    }
    return rc;
  }

  static RC multiply(const Value &left, const Value &right, Value &result)
  {
    RC rc = DataType::type_instance(result.attr_type())->multiply(left, right, result);
    if (left.get_null() || right.get_null()) {
      result.set_null();
    }
    return rc;
  }

  static RC divide(const Value &left, const Value &right, Value &result)
  {
    RC rc = DataType::type_instance(result.attr_type())->divide(left, right, result);
    if (left.get_null() || right.get_null()) {
      result.set_null();
    }
    return rc;
  }

  static RC l2_distance(const Value &left, const Value &right, Value &result)
  {
    return DataType::type_instance(AttrType::VECTORS)->l2_distance(left, right, result);

  }
  static RC cosine_distance(const Value &left, const Value &right, Value &result)
  {
    return DataType::type_instance(AttrType::VECTORS)->cosine_distance(left, right, result);

  }
  static RC inner_product(const Value &left, const Value &right, Value &result)
  {
    return DataType::type_instance(AttrType::VECTORS)->inner_product(left, right, result);

  }

  static RC negative(const Value &value, Value &result)
  {
    RC rc = DataType::type_instance(result.attr_type())->negative(value, result);
    if (value.get_null()) {
      result.set_null();
    }
    return rc;
  }

  static RC cast_to(const Value &value, AttrType to_type, Value &result)
  {

    RC rc = DataType::type_instance(value.attr_type())->cast_to(value, to_type, result);
    if (value.get_null()) {
      result.set_null();
    }
    return rc;
  }

  void set_type(AttrType type) { this->attr_type_ = type; }
  void set_data(char *data, int length);
  void set_data(const char *data, int length) { this->set_data(const_cast<char *>(data), length); }
  void set_value(const Value &value);
  void set_boolean(bool val);
  void set_null() { this->is_null_ = 1; }

  string to_string() const;

  int compare(const Value &other) const;

  const char *data() const;

  int      length() const { return length_; }
  AttrType attr_type() const { return attr_type_; }

public:
  /**
   * 获取对应的值
   * 如果当前的类型与期望获取的类型不符，就会执行转换操作
   * 并不会改变本对象成员变量
   */
  int    get_int() const;
  float  get_float() const;
  string get_string() const;
  bool   get_boolean() const;
  int    get_null() const { return is_null_; };
  time_t get_date() const;
  std::vector<float>* get_vector() const;

private:
  // bool char_to_vector(); // implicitly convert the string representation of vectors
  void set_int(int val);
  void set_float(float val);
  void set_string(const char *s, int len = 0);
  void set_string_from_other(const Value &other);
  void set_vector_from_other(const Value &other);
  void set_date(time_t t);
  void set_vector(const float* base, int len=0);

private:
  AttrType attr_type_ = AttrType::UNDEFINED;
  int      length_    = 0;
  int      is_null_   = 0;
  // [ATT!]: For a vector type, length_ => number of dimension

  union Val
  {
    int32_t int_value_;
    float   float_value_;
    bool    bool_value_;
    char   *pointer_value_;
    time_t  time_value_;
    float*  vector_value_;
  } value_ = {.int_value_ = 0};

  // 是否申请并占有内存
  // 对于 CHARS 和 VECTORS 类型 own_data_ 为true, 其余类型 own_data_ 为false
  bool own_data_ = false;
};
