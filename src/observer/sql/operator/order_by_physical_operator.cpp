#include "sql/operator/order_by_physical_operator.h"
#include "sql/expr/expression_tuple.h"
#include <algorithm>

OrderByPhysicalOperator::~OrderByPhysicalOperator() {}

RC OrderByPhysicalOperator::open(Trx *trx) {
  RC rc = RC::SUCCESS;
  rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator. rc=%s", strrc(rc));
  }

  TupleSchema schema;
  children_[0]->tuple_schema(schema);
  current_tuple_.set_names(schema.cells());

  int cell_num = schema.cell_num();

  for (size_t i = 0; i < items_.size(); i++) {
    int found_field_index = -1;
    const OrderByItem &item = items_[i];
    for (int j = 0; j < cell_num; j++) {
      const TupleCellSpec spec = schema.cell_at(j);
      string item_attr_name;
      if (strlen(item.attr.relation_name.c_str()) == 0) {
        item_attr_name = item.attr.attribute_name;
      } else {
        item_attr_name = item.attr.relation_name + "." + item.attr.attribute_name;
      }

      if (item_attr_name == spec.alias()) {
        item_indexes_.push_back(j);
        found_field_index = j;
        break;
      }
    }

    if (found_field_index == -1) {
      LOG_WARN("failed to find field %s.%s", item.attr.relation_name.c_str(), item.attr.attribute_name.c_str());
      return RC::FILE_NOT_EXIST;
    }
  }

  return rc;
}

RC OrderByPhysicalOperator::close() {
  RC rc = children_[0]->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close child operator. rc=%s", strrc(rc));
  }
  return rc;
}

RC OrderByPhysicalOperator::sort() {
  sorted_ = true;
  RC rc = RC::SUCCESS;

  while (children_[0]->next() == RC::SUCCESS) {
    auto *tuple = dynamic_cast<ExpressionTuple<std::unique_ptr<Expression>> *>(children_[0]->current_tuple());
    TupleSchema schema;
    children_[0]->tuple_schema(schema);
    int cell_num = schema.cell_num();

    OrderByTuple order_by_tuple;
    for (int i = 0; i < cell_num; i++) {
      Value cell;
      tuple->cell_at(i, cell);
      order_by_tuple.push_back(cell);
    }
    sorted_tuples_.push_back(std::move(order_by_tuple));
  }

  auto cmp_func = [&](const OrderByTuple &a, const OrderByTuple &b) {
    for (size_t i = 0; i < items_.size(); i++) {
      const OrderByItem &item = items_[i];
      const int item_idx = item_indexes_[i];
      const Value &a_val = a[item_idx], &b_val = b[item_idx];
      if (a_val.get_null() && b_val.get_null()) {
        continue;
      }
      if (a_val.get_null()) {
        return item.asc ? true : false;
      }
      if (b_val.get_null()) {
        return item.asc ? false : true;
      }

      int cmp_result = a_val.compare(b_val);
      if (cmp_result != 0) {
        return item.asc ? cmp_result < 0 : cmp_result > 0;
      }
    }
    return false;
  };

  std::sort(sorted_tuples_.begin(), sorted_tuples_.end(), cmp_func);

  return rc;
}

RC OrderByPhysicalOperator::next() {
  if (!sorted_) {
    RC rc = sort();
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  if (sorted_tuples_.empty() || ++cur_idx >= static_cast<int>(sorted_tuples_.size())) {
    return RC::RECORD_EOF;
  }

  if (cur_idx < static_cast<int>(sorted_tuples_.size())) {
    current_tuple_.set_cells(sorted_tuples_[cur_idx]);
  }
  return RC::SUCCESS;
}

Tuple *OrderByPhysicalOperator::current_tuple() {
  if (cur_idx < 0 || cur_idx >= static_cast<int>(sorted_tuples_.size())) {
    return nullptr;
  }

  return &current_tuple_;
}
