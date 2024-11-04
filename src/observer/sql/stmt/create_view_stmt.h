#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

class CreateViewStmt : public Stmt {
public:
  CreateViewStmt() {};
  CreateViewStmt(const std::string &view_name, const std::vector<std::string> &col_names, const std::string &sql_str)
      : view_name_(view_name), col_names_(col_names), sql_str_(sql_str) {}
  virtual ~CreateViewStmt() = default;
  static RC create(Db *db, CreateViewSqlNode &create_view_sql, Stmt *&stmt);

  StmtType type() const override { return StmtType::CREATE_VIEW; }
  const std::string &view_name() const { return view_name_; }
  const std::vector<std::string> &col_names() const { return col_names_; }
  const std::string &sql_str() const { return sql_str_; }

private:
  std::string view_name_;
  std::vector<std::string> col_names_;
  std::string sql_str_;
};