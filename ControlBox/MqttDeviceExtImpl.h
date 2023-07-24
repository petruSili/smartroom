#ifndef __MQTT_DEVICE_EXT_IMPL__
#define __MQTT_DEVICE_EXT_IMPL__

#include "MqttDeviceImpl.h"
#include "DeviceExt.h"
#include "Connection.h"

class MqttDeviceExtImpl:  public DeviceExt, public MqttDeviceImpl { 
public:
  MqttDeviceExtImpl(Connection* connection, const char* deviceTopic, int deviceId);
  int getId();
  int getState();
  void setState(int s);
  void switchOn();
  void switchOff();
  void changeIntensity(int i);
  int getIntensity();
  void setIntensity(int l); 
  
private:
  int intensity;
  const char* deviceTopic;
  Connection* connection;
  char intensityTopic[50];
  char buffer[10];
};

#endif
