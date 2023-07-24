#include "MqttDeviceImpl.h"
#include "LedRing.h"
#include "Connection.h"

MqttDeviceImpl::MqttDeviceImpl(Connection* connection, const char* deviceTopic, int deviceId){
  this->connection = connection;
  this->deviceId = deviceId;
  this->deviceTopic = deviceTopic;
  strcpy(powerTopic, deviceTopic);
  strcat(powerTopic, "/POWER"); 
  state = 0; 
}

int MqttDeviceImpl::getId(){
  return deviceId;
}
  
int MqttDeviceImpl::getState(){
  return state;
}

void MqttDeviceImpl::setState(int s){
  state = s;
}  

void MqttDeviceImpl::switchOn(){  
  connection->mqttPublish(powerTopic, "ON");  
}

void MqttDeviceImpl::switchOff(){
  connection->mqttPublish(powerTopic, "OFF");
}
