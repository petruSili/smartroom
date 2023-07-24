#include "PayloadGenerator.h"
#include "Configuration.h"
#include <ArduinoJson.h>
#include "Device.h"
#include "DeviceExt.h"

PayloadGenerator::PayloadGenerator(){};

char* PayloadGenerator::getDeviceState(Device* device){
  StaticJsonDocument<256> doc;
  if(device->getState() == ON){
    doc["POWER"] = "ON";
  }else{
    doc["POWER"] = "OFF";
  }
  memset(payload, 0, sizeof payload); 
  serializeJson(doc, payload); 
  return payload;
} 

char* PayloadGenerator::getDeviceExtState(DeviceExt* device){
  StaticJsonDocument<256> doc;
  if(device->getState() == ON){
    doc["POWER"] = "ON";
  }else{
    doc["POWER"] = "OFF";
  } 
  doc["Dimmer"] = device->getIntensity();
  memset(payload, 0, sizeof payload);
  serializeJson(doc, payload); 
  return payload;
}  
