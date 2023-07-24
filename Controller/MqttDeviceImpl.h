#ifndef __MQTT_DEVICE_IMPL__
#define __MQTT_DEVICE_IMPL__

#include "Device.h"
#include "MqttConnection.h"


class MqttDeviceImpl: public Device { 
public:
  MqttDeviceImpl(MqttConnection* mqttConnection, const char* deviceTopic);
  int getState();
  void setState(int s);
  void switchOn();
  void switchOff();    
protected:
  int state;
  MqttConnection* mqttConnection;
  const char* deviceTopic;
  char powerTopic[50]; 
};

#endif
