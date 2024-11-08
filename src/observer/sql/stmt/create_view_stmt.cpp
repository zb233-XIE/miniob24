#include "sql/stmt/create_view_stmt.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/optimize_stage.h"
#include "sql/optimizer/physical_plan_generator.h"

RC CreateViewStmt::create(Db *db, CreateViewSqlNode &create_view_sql, Stmt *&stmt)
{
  Stmt *select_stmt = nullptr;
  RC rc = Stmt::create_stmt(db, *create_view_sql.selection, select_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("create select stmt failed. rc=%s", strrc(rc));
    return rc;
  }

  LogicalPlanGenerator logical_plan_generator;
  PhysicalPlanGenerator physical_plan_generator;
  OptimizeStage opt_stage;
  unique_ptr<LogicalOperator> logical_oper;
  unique_ptr<PhysicalOperator> physical_oper;
  rc = logical_plan_generator.create(select_stmt, logical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create logical operator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  rc = opt_stage.rewrite(logical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to rewrite logical operator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  rc = physical_plan_generator.create(*logical_oper, physical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create physical operator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  TupleSchema schema;
  physical_oper->tuple_schema(schema);

  if (!create_view_sql.col_names.empty()) {
    if (int(create_view_sql.col_names.size()) != schema.cell_num()) {
      LOG_WARN("column number not match. expect %d, but got %d", create_view_sql.col_names.size(), schema.cell_num());
      return RC::INVALID_ARGUMENT;
    }
  } else {
    // FIXME: CHECK DUPLICATE CELL NAMES
    for (int i = 0; i < schema.cell_num(); i++) {
      TupleCellSpec spec = schema.cell_at(i);
      create_view_sql.col_names.push_back(spec.alias());
    }
  }

  auto project_oper = dynamic_cast<ProjectPhysicalOperator *>(physical_oper.get());
  auto attr_info = project_oper->attr_infos();
  auto view_meta_infos = project_oper->get_view_meta_infos();

  CreateViewStmt *create_view_stmt = new CreateViewStmt(
    create_view_sql.view_name,
    create_view_sql.col_names,
    create_view_sql.sql_str,
    attr_info,
    view_meta_infos
  );

  stmt = create_view_stmt;
  return RC::SUCCESS;
}
