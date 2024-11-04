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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/subquery_stmt.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"
#include <cstdint>
#include <memory>

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
  for (FilterStmt *filter_stmt : join_filter_stmts_) {
    delete filter_stmt;
    filter_stmt = nullptr;
  }
  if (nullptr != having_filter_stmt_) {
    delete having_filter_stmt_;
    having_filter_stmt_ = nullptr;
  }
  if (nullptr != subquery_stmt_) {
    delete subquery_stmt_;
    subquery_stmt_ = nullptr;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;
  if (stmt != nullptr) {
    SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
    for (Table *t : select_stmt->tables()) {
      binder_context.add_helper_table(t);
    }
    delete stmt;
    stmt = nullptr;
  }

  // collect tables in `from` statement
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].name.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    if (table_map.count(select_sql.relations[i].alias) != 0) {
      LOG_WARN("duplicate table alias. alias=%s", select_sql.relations[i].alias.c_str());
      return RC::TABLE_ALIAS_DUPLICATE;
    }
    table->set_alias(select_sql.relations[i].alias);
    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
    table_map.insert({select_sql.relations[i].alias, table});
  }

  // 将join语句中的表也加入到tables和table_map中，依葫芦画瓢
  for (size_t i = 0; i < select_sql.join_conditions.size(); i ++) {
    const char *table_name = select_sql.join_relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
  }

  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);
  expression_binder.set_db(db);
  
  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  // 6. 绑定select_sql.conditions中的表达式
  for (ConditionSqlNode &condition : select_sql.conditions) {
    RC rc = RC::SUCCESS;
    if (condition.neither) {
      vector<unique_ptr<Expression>> left_bound_expressions;
      vector<unique_ptr<Expression>> right_bound_expressions;
      std::unique_ptr<Expression> left_expr = std::unique_ptr<Expression>(condition.left_expr);
      std::unique_ptr<Expression> right_expr = std::unique_ptr<Expression>(condition.right_expr);
      rc = expression_binder.bind_expression(left_expr, left_bound_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind expression failed. rc=%s", strrc(rc));
        return rc;
      }
      rc = expression_binder.bind_expression(right_expr, right_bound_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind expression failed. rc=%s", strrc(rc));
        return rc;
      }
      condition.left_expr = left_bound_expressions[0].release();
      condition.right_expr = right_bound_expressions[0].release();
    }
  }

  // 10. 在conditions中删除子查询的内容，因为后面要根据conditions构建filter stmt
  std::vector<ConditionSqlNode> subquery_conditions;
  for (auto it = select_sql.conditions.begin(); it != select_sql.conditions.end(); ) {
    if (it->is_subquery) {
      subquery_conditions.push_back(std::move(*it));
      it = select_sql.conditions.erase(it);
    } else {
      it++;
    }
  }

  // 9. 绑定select_sql.join_conditions中的表达式
  for (std::vector<ConditionSqlNode> *conditions : select_sql.join_conditions) {
    for (ConditionSqlNode &condition : *conditions) {
      RC rc = RC::SUCCESS;
      if (condition.neither) {
        vector<unique_ptr<Expression>> left_bound_expressions;
        vector<unique_ptr<Expression>> right_bound_expressions;
        std::unique_ptr<Expression>    left_expr  = std::unique_ptr<Expression>(condition.left_expr);
        std::unique_ptr<Expression>    right_expr = std::unique_ptr<Expression>(condition.right_expr);
        rc = expression_binder.bind_expression(left_expr, left_bound_expressions);
        if (OB_FAIL(rc)) {
          LOG_INFO("bind expression failed. rc=%s", strrc(rc));
          return rc;
        }
        rc = expression_binder.bind_expression(right_expr, right_bound_expressions);
        if (OB_FAIL(rc)) {
          LOG_INFO("bind expression failed. rc=%s", strrc(rc));
          return rc;
        }
        condition.left_expr  = left_bound_expressions[0].release();
        condition.right_expr = right_bound_expressions[0].release();
      }
    }
  }

  // 18. 绑定select_sql.having中的表达式
  for (ConditionSqlNode &condition : select_sql.having) {
    RC rc = RC::SUCCESS;
    if (condition.neither) {
      vector<unique_ptr<Expression>> left_bound_expressions;
      vector<unique_ptr<Expression>> right_bound_expressions;
      std::unique_ptr<Expression> left_expr = std::unique_ptr<Expression>(condition.left_expr);
      std::unique_ptr<Expression> right_expr = std::unique_ptr<Expression>(condition.right_expr);
      rc = expression_binder.bind_expression(left_expr, left_bound_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind expression failed. rc=%s", strrc(rc));
        return rc;
      }
      rc = expression_binder.bind_expression(right_expr, right_bound_expressions);
      if (OB_FAIL(rc)) {
        LOG_INFO("bind expression failed. rc=%s", strrc(rc));
        return rc;
      }
      condition.left_expr = left_bound_expressions[0].release();
      condition.right_expr = right_bound_expressions[0].release();
    }
  }


  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // 10. 为subquery构造subquery statement
  SubqueryStmt *subquery_stmt = nullptr;
  rc                          = SubqueryStmt::create(db,
      default_table,
      &table_map,
      subquery_conditions.data(),
      static_cast<int>(subquery_conditions.size()),
      subquery_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct subquery stmt");
    return rc;
  }

  // 9. 为join中的所有on构造filter statement
  vector<FilterStmt *> filter_stmts;
  for (size_t i = 0; i < select_sql.join_conditions.size(); i ++) {
    auto &conditions = select_sql.join_conditions[i];
    FilterStmt *filter_stmt = nullptr;
    RC          rc          = FilterStmt::create(db,
        default_table,
        &table_map,
        (*conditions).data(),
        static_cast<int>((*conditions).size()),
        filter_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
    filter_stmts.push_back(filter_stmt);
    // join_conditions中的元素是指针，无法自动释放，手动delete
    // vector析构时同时会析构里面的元素，即ConditionSqlNode
    // FilterUnit中的left_expr和right_expr是expression指针，来自ConditionSqlNode
    // 但是指针类型不会被自动析构，因此这里delete没有问题
    delete conditions;
  }

  // 18. 为having构造filter statement
  FilterStmt *having_filter_stmt = nullptr;
  rc                             = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.having.data(),
      static_cast<int>(select_sql.having.size()),
      having_filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }
  
  // 17. create orderby stmt
  OrderByStmt *order_by_stmt;
  if (select_sql.order_by.empty()) {
    order_by_stmt = nullptr;
  } else {
    order_by_stmt = new OrderByStmt(select_sql.order_by); 
  }

  for (Table *t: tables) {
    t->unset_alias();
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->join_filter_stmts_.swap(filter_stmts);
  select_stmt->having_filter_stmt_ = having_filter_stmt;
  select_stmt->subquery_stmt_ = subquery_stmt;
  select_stmt->order_by_ = order_by_stmt;
  stmt                      = select_stmt;
  return RC::SUCCESS;
}
