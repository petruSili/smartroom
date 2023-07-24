#ifndef __HOME_PRESENCE_TASK__
#define __HOME_PRESENCE_TASK__

#include "Task.h"
#include "Configuration.h"

class HomePresenceTask: public Task {
  
public:

  HomePresenceTask();  
  void init(int period);  
  void tick();
};

#endif
