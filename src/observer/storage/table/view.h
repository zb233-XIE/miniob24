#pragma once

#include "common/rc.h"
#include "storage/field/field_meta.h"
#include <map>
#include <string>
#include <vector>

class SelectStmt;
class Db;
class Table;

struct ViewMetaInfo {
  int expr_type;
  std::string field_name;
  std::string table_name;
};

class View {
public:
  View(const std::string &name, const std::vector<std::string> &col_names, const std::string &sql_str, Db *db, const std::vector<ViewMetaInfo> &view_meta_infos)
      : name_(name), col_names_(col_names), sql_str_(sql_str), db_(db), view_meta_infos_(view_meta_infos) {}
  ~View() = default;
  const std::string &name() const { return name_; }
  const std::vector<std::string> &col_names() const { return col_names_; }
  const std::string &sql_str() const { return sql_str_; }
  RC create_select_stmt(SelectStmt *&select_stmt);

  void init_fields(const std::vector<AttrInfoSqlNode> &attr_infos);
  const std::vector<FieldMeta> &fields() const { return fields_; }
  const FieldMeta *field(const char *name) const;
  const FieldMeta *field(int i) const { return &fields_[i]; }
  int field_num() const { return fields_.size(); }

  bool is_lookup_map_set() const { return is_lookup_map_set_; }
  void set_lookup_map(const std::map<std::string, std::string> &lookup_map) {
    lookup_map_ = lookup_map;
    is_lookup_map_set_ = true;
  }

  RC look_up(const std::string &name, std::string &alias) const {
    auto it = lookup_map_.find(name);
    if (it == lookup_map_.end()) {
      return RC::VIEW_ALIAS_NOT_FOUND;
    }
    alias = it->second;
    return RC::SUCCESS;
  }

  bool is_field_col_trans_enabled() const { return col_field_trans_enabled_; }
  void insert_col_field(std::string col, std::string field) {
    col_field_trans_enabled_ = true;
    col2field_[col] = field;
    field2col_[field] = col;
  }
  RC col_to_field_lookup(const std::string &col, std::string &field) const {
    auto it = col2field_.find(col);
    if (it == col2field_.end()) {
      return RC::FIELD_NOT_FOUND;
    }
    field = it->second;
    return RC::SUCCESS;
  }
  RC field_to_col_lookup(const std::string &field, std::string &col) const {
    auto it = field2col_.find(field);
    if (it == field2col_.end()) {
      return RC::FIELD_NOT_FOUND;
    }
    col = it->second;
    return RC::SUCCESS;
  }

  Table *handle_view_insert(std::vector<int> &indexes);
  Table *handle_view_update(std::vector<std::string> field_names, std::vector<FieldMeta> &update_fields);
  Table *handle_view_delete();

private:
  std::string name_;
  std::vector<std::string> col_names_;
  std::string sql_str_;
  Db *db_;
  std::vector<ViewMetaInfo> view_meta_infos_;

  std::vector<FieldMeta> fields_;
  bool is_lookup_map_set_ = false;
  std::map<std::string, std::string> lookup_map_; // view_name.field_name -> sub_select_stmt.alias

  bool col_field_trans_enabled_ = false;
  std::map<std::string, std::string> col2field_;
  std::map<std::string, std::string> field2col_;
};
