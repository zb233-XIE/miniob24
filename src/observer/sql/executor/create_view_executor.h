#include "common/rc.h"
#include "event/sql_event.h"

class CreateViewExecutor {
public:
  CreateViewExecutor()          = default;
  virtual ~CreateViewExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};