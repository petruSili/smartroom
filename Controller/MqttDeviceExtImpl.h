#ifndef __MQTT_DEVICE_EXT_IMPL__
#define __MQTT_DEVICE_EXT_IMPL__

#include "DeviceExt.h"
#include "MqttDeviceImpl.h"
#include "MqttConnection.h"

class MqttDeviceExtImpl:  public DeviceExt, public MqttDeviceImpl { 
public:
  MqttDeviceExtImpl(MqttConnection* mqttConnection, const char* deviceTopic);
  int getState();
  void setState(int s);
  void switchOn();
  void switchOff(); 
  int getIntensity();
  void setIntensity(int i);
  void changeIntensity(int i); 
  
private:
  int intensity;
  const char* deviceTopic;
  MqttConnection* mqttConnection;
  char intensityTopic[50];
  char buffer[10];
};

#endif
