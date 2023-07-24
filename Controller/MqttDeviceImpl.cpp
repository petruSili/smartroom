#include "MqttDeviceImpl.h"
#include "MqttConnection.h"

MqttDeviceImpl::MqttDeviceImpl(MqttConnection* mqttConnection, const char* deviceTopic){
  this->mqttConnection = mqttConnection;
  this->deviceTopic = deviceTopic;
  strcpy(powerTopic, deviceTopic);
  strcat(powerTopic, "/POWER"); //---- Composes the topic to send ON/OFF commands
  state = 0; 
}

 int MqttDeviceImpl::getState(){
  return state;
}

void MqttDeviceImpl::setState(int s){
  state = s;
}  

void MqttDeviceImpl::switchOn(){  
  mqttConnection->clientPublish(powerTopic, "ON");
}

void MqttDeviceImpl::switchOff(){
  mqttConnection->clientPublish(powerTopic, "OFF");
}
