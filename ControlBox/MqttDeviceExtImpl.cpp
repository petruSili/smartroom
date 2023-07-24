#include "MqttDeviceExtImpl.h"
#include "MqttDeviceImpl.h"
#include "Connection.h"

MqttDeviceExtImpl::MqttDeviceExtImpl(Connection* connection, const char* deviceTopic, int deviceId) : MqttDeviceImpl(connection, deviceTopic, deviceId) {
  this->connection = connection;
  this->deviceId = deviceId;
  this->deviceTopic = deviceTopic;
  strcpy(powerTopic, deviceTopic);
  strcat(powerTopic, "/POWER");
  strcpy(intensityTopic, deviceTopic);
  strcat(intensityTopic, "/Dimmer");
  intensity = 0;
  state = 0;
}

int MqttDeviceExtImpl::getId(){
  return deviceId;
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

void MqttDeviceExtImpl::changeIntensity(int i){                                 
 dtostrf(i,3, 0, buffer);                        
 Serial.print(intensityTopic);
 Serial.println(buffer);
 connection->mqttPublish(intensityTopic, buffer);
 
}

void MqttDeviceExtImpl::setIntensity(int i){
  intensity = i;
}  

void MqttDeviceExtImpl::switchOn(){
  MqttDeviceImpl::switchOn();
}

void MqttDeviceExtImpl::switchOff(){
  MqttDeviceImpl::switchOff();
}
