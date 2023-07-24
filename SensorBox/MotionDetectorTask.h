#ifndef __MOTIONDETECTORTASK__
#define __MOTIONDETECTORTASK__

#include "Task.h"
#include "Connection.h"
#include "PirSensor.h"

class MotionDetectorTask: public Task {

  Connection* connection;
  PirSensor* pirSensor;
public:

  MotionDetectorTask(Connection* connection);  
  void init(int period);  
  void tick();
};

#endif
