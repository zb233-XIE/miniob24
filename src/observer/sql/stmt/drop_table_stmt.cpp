#include "sql/stmt/drop_table_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

RC DropTableStmt::create(Db *db, const DropTableSqlNode &drop_table, Stmt *&stmt) {
  stmt = nullptr;

  const char *table_name = drop_table.relation_name.c_str();
  if (common::is_blank(table_name)) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  Table *table = db->find_table(table_name);
  if (table == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  stmt = new DropTableStmt(table_name);
  return RC::SUCCESS;
}
