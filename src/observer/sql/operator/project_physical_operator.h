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
// Created by WangYunlai on 2022/07/01.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/expr/expression_tuple.h"
#include "storage/table/view.h"

/**
 * @brief 选择/投影物理算子
 * @ingroup PhysicalOperator
 */
class ProjectPhysicalOperator : public PhysicalOperator
{
public:
  ProjectPhysicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions);

  virtual ~ProjectPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::PROJECT; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const { return tuple_.cell_num(); }

  Tuple *current_tuple() override;

  RC tuple_schema(TupleSchema &schema) const override;

  void set_multi_tables_flag() { multi_tables_flag_ = 1; }
  int get_multi_tables_flag() const { return multi_tables_flag_; }

  void set_has_view_flag() { has_view_flag_ = 1; }
  int get_has_view_flag() const { return has_view_flag_; }

  std::vector<AttrInfoSqlNode> attr_infos() {
    std::vector<AttrInfoSqlNode> attr_infos;
    for (size_t i = 0; i < expressions_.size(); i++) {
      AttrInfoSqlNode attr_info;
      // check if attr_info.name has the form table_name.field_name
      // if yes, set name to field_name
      attr_info.name = expressions_[i]->name();
      size_t pos = attr_info.name.find(".");
      if (pos != std::string::npos) {
        attr_info.name = attr_info.name.substr(pos + 1);
      }
      attr_info.type = expressions_[i]->value_type();
      attr_info.length = expressions_[i]->value_length();
      attr_info.nullable = true;
      attr_infos.push_back(attr_info);
    }
    return attr_infos;
  }

  std::vector<ViewMetaInfo> get_view_meta_infos() {
    std::vector<ViewMetaInfo> view_meta_infos;
    for (size_t i = 0; i < expressions_.size(); i++) {
      ViewMetaInfo info;
      info.expr_type = (int)expressions_[i]->type();
      if (expressions_[i]->type() == ExprType::FIELD) {
        FieldExpr *field_expr = static_cast<FieldExpr *>(expressions_[i].get());
        info.table_name = field_expr->table_name();
        info.field_name = field_expr->field_name();
      }
      view_meta_infos.push_back(info);
    }

    return view_meta_infos;
  }

private:
  std::vector<std::unique_ptr<Expression>>     expressions_;
  ExpressionTuple<std::unique_ptr<Expression>> tuple_;
  int multi_tables_flag_ = 0;
  int has_view_flag_ = 0;
  ValueListTuple view_tuple_;
};
