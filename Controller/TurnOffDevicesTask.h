/*The TurnOffDevicesTask manages the nightLamps 
 * by turning them ON to provide a minimum amount of visibility
 * when the room is DARK and switches them OFF when it's BRIGHT to save power.
 */
#include "Configuration.h"

#ifndef __TURNOFF_DEVICES_TASK__
#define __TURNOFF_DEVICES_TASK__

#include "Task.h"
#include "Device.h"

class TurnOffDevicesTask: public Task {
  Device** allDevices;
public:

  TurnOffDevicesTask(Device* devices[]);  
  void init(int period);  
  void tick();
};

#endif
