#include "MqttDeviceExtImpl.h"
#include "MqttDeviceImpl.h"
#include "MqttConnection.h"

MqttDeviceExtImpl::MqttDeviceExtImpl(MqttConnection* mqttConnection, const char* deviceTopic) : MqttDeviceImpl(mqttConnection, deviceTopic) {
  this->mqttConnection = mqttConnection;
  this->deviceTopic = deviceTopic;
  strcpy(powerTopic, deviceTopic);
  strcat(powerTopic, "/POWER"); //---------- Composes the topic to send ON/OFF commands
  strcpy(intensityTopic, deviceTopic);
  strcat(intensityTopic, "/Dimmer");  //---- Composes the topic to send INTENSITY commands
  intensity = 0;
  state = 0;
}

int MqttDeviceExtImpl::getState(){
  return state;
}

int MqttDeviceExtImpl::getIntensity(){
  return intensity;
}

void MqttDeviceExtImpl::setState(int s){
  state = s;
}  
void MqttDeviceExtImpl::setIntensity(int i){
  intensity = i;
}
void MqttDeviceExtImpl::changeIntensity(int i){
 dtostrf(i,3, 0, buffer); 
 mqttConnection->clientPublish(intensityTopic, buffer);
}  

void MqttDeviceExtImpl::switchOn(){
  MqttDeviceImpl::switchOn();
}

void MqttDeviceExtImpl::switchOff(){
  MqttDeviceImpl::switchOff();
}
  
