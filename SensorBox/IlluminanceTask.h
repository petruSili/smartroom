#ifndef __ILLUMINANCETASK__
#define __ILLUMINANCETASK__

#include "Task.h"
#include "IlluminanceSensor.h"
#include "Connection.h"

class IlluminanceTask: public Task {

  IlluminanceSensor* illumSensor;
  Connection* connection;
  float illuminance;
  float newIlluminance;
  char buffer[10];

public:

  IlluminanceTask(Connection* connection);  
  void init(int period);  
  void tick();
};

#endif
