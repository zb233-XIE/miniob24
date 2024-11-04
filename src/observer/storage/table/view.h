#pragma once
#include "common/rc.h"
#include <string>
#include <vector>

class SelectStmt;
class Db;

class View {
public:
  View(const std::string &name, const std::vector<std::string> &col_names, const std::string &sql_str, Db *db)
      : name_(name), col_names_(col_names), sql_str_(sql_str), db_(db) {}
  ~View() = default;
  const std::string &name() const { return name_; }
  const std::vector<std::string> &col_names() const { return col_names_; }
  const std::string &sql_str() const { return sql_str_; }
  RC create_select_stmt(SelectStmt *&select_stmt);

private:
  std::string name_;
  std::vector<std::string> col_names_;
  std::string sql_str_;
  Db *db_;
};
