#include "MqttParseAndUpdate.h"
#include"Configuration.h"
#include <ArduinoJson.h>
#include"Arduino.h"
#include"Device.h"
#include"DeviceExt.h"

/*The payload is structured in Json format, hence the <ArduimoJson.h> library for device state extraction*/

MqttParseAndUpdate::MqttParseAndUpdate(){};

void MqttParseAndUpdate::updateDevice( char* payload, Device* device){ 
  const char* power;
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, (const char*)payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }else{
    power = doc["POWER"];
    if(strcmp(power, "ON") == 0){
      device->setState(ON);
    }else if(strcmp(power, "OFF") == 0){
      device->setState(OFF);
    }
  }  
}

void MqttParseAndUpdate::updateDeviceExt(char* payload, DeviceExt* device){
  const char* power;
  int intensity;
  
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, (const char*)payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    Serial.println(payload);
    return;
  }else{      
    power = doc["POWER"];
    intensity = doc["Dimmer"] | -1; //--------------- If the value is not present in the payload -1 is the default. 
    if(strcmp(power, "ON") == 0){
      device->setState(ON);
    }else if(strcmp(power, "OFF") == 0){
      device->setState(OFF);
    }   
    if(intensity != -1){   
      device->setIntensity(intensity);
    }
  }
}  

void MqttParseAndUpdate::setPowerSave(char* payload){
  const char* sleepMode;
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, (const char*)payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }else{ 
    sleepMode = doc["POWERSAVE"];
    if(strcmp(sleepMode, "ON") == 0){
      ecoMode = true;
    }else if(strcmp(sleepMode, "OFF") == 0){
      ecoMode = false;
    }
  } 
}
