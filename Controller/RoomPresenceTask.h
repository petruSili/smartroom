#ifndef __ROOM_PRESENCE_TASK__
#define __ROOM_PRESENCE_TASK__

#include "Task.h"
#include "Configuration.h"

class RoomPresenceTask: public Task {
  
public:

  RoomPresenceTask();  
  void init(int period);  
  void tick();
};

#endif
