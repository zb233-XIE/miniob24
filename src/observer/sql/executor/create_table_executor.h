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
// Created by Wangyunlai on 2023/6/13.
//

#pragma once

#include "common/rc.h"
#include "sql/operator/physical_operator.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/select_stmt.h"

class SQLStageEvent;

/**
 * @brief 创建表的执行器
 * @ingroup Executor
 */
class CreateTableExecutor
{
public:
  CreateTableExecutor()          = default;
  virtual ~CreateTableExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
  RC generate_physical_plan(Db *db, CreateTableStmt *create_stmt, std::unique_ptr<PhysicalOperator> &physical_oper);
  RC get_attrs_from_subq(Db *db, CreateTableStmt *create_stmt, std::unique_ptr<PhysicalOperator> &physical_oper);
  RC insert_records_from_subq(std::unique_ptr<PhysicalOperator> &physical_oper, Table *table);
};