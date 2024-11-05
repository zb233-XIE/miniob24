#include "sql/operator/view_get_physical_operator.h"

RC ViewGetPhysicalOperator::open(Trx *trx) {
  RC rc = RC::SUCCESS;
  rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator. rc=%s", strrc(rc));
  }

  return rc;
}

RC ViewGetPhysicalOperator::close() {
  RC rc = children_[0]->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close child operator. rc=%s", strrc(rc));
  }
  return rc;
}

RC ViewGetPhysicalOperator::next() {
  return children_[0]->next();
}

Tuple *ViewGetPhysicalOperator::current_tuple() {
  Tuple *tuple = children_[0]->current_tuple();
  std::vector<TupleCellSpec> specs;
  std::vector<Value> cells;

  int cell_num = tuple->cell_num();
  for (int i = 0; i < cell_num; i++) {
    TupleCellSpec spec;
    tuple->spec_at(i, spec);
    specs.push_back(spec);
    Value cell;
    tuple->cell_at(i, cell);
    cells.push_back(cell);
  }

  if (!view_->is_lookup_map_set()) {
    std::map<std::string, std::string> lookup_map;
    for (int i = 0; i < cell_num; i++) {
      lookup_map[view_->name() + "." + view_->col_names()[i]] = specs[i].alias();
    }
    view_->set_lookup_map(lookup_map);
  }

  tuple_.set_names(specs);
  tuple_.set_cells(cells);

  return &tuple_;
}

RC ViewGetPhysicalOperator::tuple_schema(TupleSchema &schema) const {
  TupleSchema child_schema;
  RC rc = children_[0]->tuple_schema(child_schema);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get child schema. rc=%s", strrc(rc));
  }

  TupleSchema view_schema;
  if (view_->is_field_col_trans_enabled()) {
    int cell_num = child_schema.cell_num();
    for (int i = 0; i < cell_num; i++) {
      TupleCellSpec spec = child_schema.cell_at(i);
      std::string view_alias;
      rc = view_->field_to_col_lookup(spec.alias(), view_alias);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      view_schema.append_cell(view_alias.c_str());
    }
    schema = view_schema;
  } else {
    schema = child_schema;
  }

  return rc;
}
