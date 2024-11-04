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

  tuple_.set_names(specs);
  tuple_.set_cells(cells);

  return &tuple_;
}

RC ViewGetPhysicalOperator::tuple_schema(TupleSchema &schema) const {
  return children_[0]->tuple_schema(schema);
}
