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

/**
 * @brief 属性的类型
 * @details AttrType 枚举列出了属性的各种数据类型。
 */
#include <cstdint>
#include <common/types.h>

enum class AttrType
{
  UNDEFINED,
  CHARS,     ///< 字符串类型
  INTS,      ///< 整数类型(4字节)
  FLOATS,    ///< 浮点数类型(4字节)
  DATES,     ///< 日期类型时间戳(8字节)
  VECTORS,   ///< 向量类型
  TEXTS,     ///< 超大字符串类型
  BOOLEANS,  ///< boolean类型，当前不是由parser解析出来的，是程序内部使用的
  MAXTYPE,   ///< 请在 UNDEFINED 与 MAXTYPE 之间增加新类型
};

static constexpr int LOB_OVERFLOW_THRESHOLD = 1000 + sizeof(PageNum);
static constexpr int LOB_VECTOR_OVERFLOW_DIM = (LOB_OVERFLOW_THRESHOLD / sizeof(float));
// static constexpr int LOB_VECTOR_OVERFLOW_DIM = 4;  // dim >= LOB_VECTOR_OVERFLOW_DIM
static constexpr int LOB_MAX_SIZE            = UINT16_MAX;
static constexpr int LOB_VECTOR_MAX_DIM      = 16000;

const char *attr_type_to_string(AttrType type);
AttrType    attr_type_from_string(const char *s);
