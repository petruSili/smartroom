/*
 * The AwakeIlluminanceTask manages the nightLamps 
 * by turning them ON to provide a minimum amount of visibility
 * when the room is DARK and switches them OFF when it's BRIGHT to save power.
 */

#ifndef __AWAKE_ILLUMINANCE_TASK__
#define __AWAKE_ILLUMINANCE_TASK__

#include "Task.h"
#include "Device.h"

class AwakeIlluminanceTask: public Task {

  Device* nightLamps;

public:

  AwakeIlluminanceTask(Device* nightLamps);  
  void init(int period);  
  void tick();
};

#endif
