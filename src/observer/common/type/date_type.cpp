#include "common/type/date_type.h"
#include "common/value.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"

int DateType::compare(const Value &left, const Value &right) const {
  ASSERT(left.attr_type() == AttrType::DATES && right.attr_type() == AttrType::DATES, "invalid type");
  time_t t1 = left.get_date();
  time_t t2 = right.get_date();
  return common::compare_time((void *)&t1, (void *)&t2);
}

RC DateType::to_string(const Value &val, string &result) const {
  time_t timestamp = val.get_date();
  char buf[16]; bzero(buf, 16);
  struct tm tm; bzero(&tm, sizeof(tm));

  localtime_r(&timestamp, &tm);
  strftime(buf, 16, "%Y-%m-%d", &tm);
  result = string(buf);
  return RC::SUCCESS;
}