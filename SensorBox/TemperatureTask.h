#ifndef __TEMPERATURETASK__
#define __TEMPERATURETASK__

#include "Task.h"
#include "TemperatureSensor.h"
#include "Connection.h"

class TemperatureTask: public Task {

  TemperatureSensor* tempSensor;
  Connection* connection;
  float temperature;
  float humidity;
  float heatIndex;
  float newTemperature;
  float newHumidity;
  float newHeatIndex;
  char buffer[10];

public:

  TemperatureTask(Connection* connection);  
  void init(int period);  
  void tick();
};

#endif
