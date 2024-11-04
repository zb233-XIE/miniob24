#include "storage/table/view.h"
#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"

RC View::create_select_stmt(SelectStmt *&select_stmt) {
  ParsedSqlResult parse_result;
  RC rc = parse(sql_str_.c_str(), &parse_result);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to parse sql. rc=%s", strrc(rc));
    return rc;
  }
  if (parse_result.sql_nodes().empty()) {
    LOG_WARN("failed to parse sql");
    return RC::INTERNAL;
  }
  if (parse_result.sql_nodes().size() > 1) {
    LOG_WARN("got multi sql commands but only 1 will be handled");
  }

  std::unique_ptr<ParsedSqlNode> sql_node = std::move(parse_result.sql_nodes()[0]);
  ParsedSqlNode *p_sql_node = sql_node.get();
  Stmt *stmt = nullptr;
  rc = Stmt::create_stmt(db_, *p_sql_node, stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create stmt. rc=%s", strrc(rc));
    return rc;
  }

  select_stmt = static_cast<SelectStmt *>(stmt);
  return rc;
}
