#include "common/rc.h"
#include "common/type/data_type.h"

#pragma once

class DateType: public DataType
{
public:
  DateType(): DataType(AttrType::DATES) {}
  virtual ~DateType() {};

  int compare(const Value &left, const Value &right) const override;
  RC to_string(const Value &val, string &result) const override;
};