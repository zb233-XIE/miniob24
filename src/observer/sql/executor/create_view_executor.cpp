#include "sql/executor/create_view_executor.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/create_view_stmt.h"
#include "storage/db/db.h"

RC CreateViewExecutor::execute(SQLStageEvent *sql_event) {
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_VIEW,
      "create view executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  CreateViewStmt *create_stmt = static_cast<CreateViewStmt *>(stmt);
  RC rc = session->get_current_db()->create_view(create_stmt->view_name().c_str(), create_stmt->col_names(),
                                    create_stmt->sql_str(), create_stmt->attr_infos(), create_stmt->view_meta_infos());
  return rc;
}
