#ifndef __MQTT_DEVICE_IMPL__
#define __MQTT_DEVICE_IMPL__

#include "Device.h"
#include "Connection.h"

class MqttDeviceImpl: public Device { 
public:
  MqttDeviceImpl(Connection* connection, const char* deviceTopic, int deviceId);
  int getId();
  int getState();
  void setState(int s);
  void switchOn();
  void switchOff();    
protected:
  int state;
  int deviceId;
  Connection* connection;
  const char* deviceTopic;
  char powerTopic[50]; 
};

#endif
