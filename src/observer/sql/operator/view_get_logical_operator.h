#include "sql/operator/logical_operator.h"

class ViewGetLogicalOperator : public LogicalOperator {
public:
  ViewGetLogicalOperator() {};
  ViewGetLogicalOperator(View *view, ReadWriteMode mode) : view_(view), mode_(mode) {}
  ~ViewGetLogicalOperator() {};

  LogicalOperatorType type() const override { return LogicalOperatorType::VIEW_GET; }
  View *view() const { return view_; }
  ReadWriteMode read_write_mode() const { return mode_; }

private:
  View *view_;
  ReadWriteMode mode_ = ReadWriteMode::READ_WRITE;
};