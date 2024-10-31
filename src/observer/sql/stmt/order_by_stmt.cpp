#include "sql/stmt/order_by_stmt.h"

OrderByStmt::OrderByStmt(const std::vector<OrderByItem> &items) : items_(items) {}
