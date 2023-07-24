#ifndef __COOLING_TASK__
#define __COOLING_TASK__

#include "Task.h"
#include "DeviceExt.h"

class CoolingTask: public Task {

  DeviceExt* device;
  

public:

  CoolingTask(DeviceExt* device);  
  void init(int period);  
  void tick();
};

#endif
