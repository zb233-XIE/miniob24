#include "sql/stmt/stmt.h"

class OrderByUnit {
};

class OrderByStmt : public Stmt {
public:
  OrderByStmt(const std::vector<OrderByItem> &items);
  ~OrderByStmt() override = default;

  StmtType type() const override { return StmtType::ORDER_BY; }
  const std::vector<OrderByItem> &items() const { return items_; }

private:
  std::vector<OrderByItem> items_;
};
