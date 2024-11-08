#include "storage/table/view.h"
#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"
#include "storage/db/db.h"

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

void View::init_fields(const std::vector<AttrInfoSqlNode> &attr_infos) {
  int offset = 0;
  for (size_t i = 0; i < attr_infos.size(); i++) {
    const AttrInfoSqlNode &attr_info = attr_infos[i];
    FieldMeta field(col_names_[i].c_str(), attr_info.type, offset, attr_info.length, true, i, attr_info.nullable);
    fields_.push_back(field);
    offset += attr_info.length;
  }

  
}

const FieldMeta *View::field(const char *name) const {
  if (nullptr == name) {
    return nullptr;
  }
  for (const FieldMeta &field : fields_) {
    if (0 == strcmp(field.name(), name)) {
      return &field;
    }
  }
  return nullptr;
}

Table *View::handle_view_insert(std::vector<int> &indexes) {
  Table *insert_table = nullptr, *table = nullptr;
  for (int i = 0; i < fields_.size(); i++) {
    // view constructed from non-field expression is not insertable
    if (view_meta_infos_[i].expr_type != int(ExprType::FIELD)) {
      return nullptr;
    }

    table = db_->find_table(view_meta_infos_[i].table_name.c_str());
    if (table == nullptr) {
      return nullptr;
    }
    if (insert_table == nullptr) {
      insert_table = table;
    }
    // view constructed from joined expression(multiple tables) is not insertable
    if (insert_table != table) {
      return nullptr;
    }
  }

  auto table_meta = insert_table->table_meta();
  for (int i = table_meta.sys_field_num(); i < table_meta.field_num(); i++) {
    bool found = false;
    for (int j = 0; j < view_meta_infos_.size(); j++) {
      if (view_meta_infos_[j].field_name == table_meta.field(i)->name()) {
        indexes.push_back(j);
        found = true;
        break;
      }
    }

    if (!found) {
      if (table_meta.field(i)->nullable()) {
        indexes.push_back(-1);
      } else {
        return nullptr;
      }
    }
  }

  return insert_table;
}

Table *View::handle_view_update(std::vector<std::string> field_name, std::vector<FieldMeta> &update_fields) {
  // check aggregation
  for (const ViewMetaInfo &info : view_meta_infos_) {
    if (info.expr_type == int(ExprType::AGGREGATION)) {
      return nullptr;
    }
  }

  // check field name
  Table *update_table = nullptr, *table = nullptr;
  for (const std::string &name : field_name) {
    bool found = false;
    for (size_t i = 0; i < view_meta_infos_.size(); i++) {
      if (view_meta_infos_[i].field_name == name) {
        table = db_->find_table(view_meta_infos_[i].table_name.c_str());
        if (table == nullptr) {
          return nullptr;
        }
        if (update_table == nullptr) {
          update_table = table;
        }
        if (update_table != table) {
          return nullptr;
        }
        update_fields.push_back(*table->table_meta().field(name.c_str()));
        found = true;
        break;
      }
    }
    if (!found) {
      return nullptr;
    }
  }

  return update_table;
}

Table *View::handle_view_delete() {
  // check aggregation
  for (const ViewMetaInfo &info : view_meta_infos_) {
    if (info.expr_type == int(ExprType::AGGREGATION)) {
      return nullptr;
    }
  }

  // check field name
  Table *delete_table = nullptr, *table = nullptr;
  for (const ViewMetaInfo &info : view_meta_infos_) {
    table = db_->find_table(info.table_name.c_str());
    if (table == nullptr) {
      return nullptr;
    }
    if (delete_table == nullptr) {
      delete_table = table;
    }
    if (delete_table != table) {
      return nullptr;
    }
  }

  return delete_table;
}
