/*
 * Class that parses the MQTT message and updates the state of the device the message refers to.
*/

#ifndef __MQTT_PARSE_AND_UPDATE__
#define __MQTT_PARSE_AND_UPDATE__

#include"Configuration.h"
#include"Device.h"
#include"DeviceExt.h"

class MqttParseAndUpdate {
  
public: 
  MqttParseAndUpdate();
  void updateDevice( char* payload, Device* device);
  void updateDeviceExt( char* payload, DeviceExt* device);
  void setPowerSave(char* payload); 
};

#endif
