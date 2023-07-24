#ifndef __ASLEEP_ILLUMINANCE_TASK__
#define __ASLEEP_ILLUMINANCE_TASK__

#include "Task.h"
#include "Device.h"
#include "Configuration.h"

class AsleepIlluminanceTask: public Task {

  Device* nightLamps;
  long timerStart;

public:

  AsleepIlluminanceTask(Device* nightLamps);  
  void init(int period);  
  void tick();
};

#endif
