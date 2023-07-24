#include "PayloadParser.h"
#include "Configuration.h"
#include <ArduinoJson.h>


PayloadParser::PayloadParser(){};

int PayloadParser::parseDeviceId(char* payload){ 
  const char* device; 
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, (const char*)payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }else{  
    Serial.println(F("test parseDeviceId"));
    device = doc["DEVICE"];
  
    if(strcmp(device, "deskLamp") == 0){
      return deskLamp_ID;
    }else if(strcmp(device, "mainLight") == 0){
      return mainLight_ID;
    }else if(strcmp(device, "arduinoFan") == 0){
      return arduinoFan_ID;
    }else if(strcmp(device, "autoMode") == 0){
      return isAuto_ID;
    }else if(strcmp(device, "sleeping") == 0){
      return isAsleep_ID;
    } 
  }
}

int PayloadParser::parsePowerStat(char* payload){ 
  Serial.print(F("parsePowerStat: "));
  Serial.println(payload);
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
      return ON;
    }else if(strcmp(power, "OFF") == 0){
      return OFF;
    } 
  }
}

int PayloadParser::parseIntensityStat( char* payload){
  int intensity;
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, (const char*)payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }else{  
    intensity = doc["Dimmer"] | -1;     
     
    return intensity;
  }
}  

int PayloadParser::parsePowerCmnd(char* payload){ 
  if(strcmp(payload, "ON") == 0){
    return ON;
  }else if(strcmp(payload, "OFF") == 0){
    return OFF;
  }  
}

int PayloadParser::parseIntensityCmnd(char* payload){
  return atoi(payload);
}

bool PayloadParser::parseHomePresence(char* payload){
  if(strcmp(payload, "ON") == 0){
    return true;
  }else{
    return false;
  }
}

bool PayloadParser::parseRoomPresence(char* payload){
  if(strcmp(payload, "ON") == 0){
    return true;
  }else{
    return false;
  } 
}  
   
double PayloadParser::parseRoomIlluminance(char* payload){
  return atof(payload);  
}

double PayloadParser::parseRoomTemperature(char* payload){
  return atof(payload);
}

double PayloadParser::parseRoomHumidity(char* payload){
  return atof(payload);  
}

double PayloadParser::parseRoomHeatIndex(char* payload){
  return atof(payload);
}

int PayloadParser::parseMode(char* payload){
  return atoi(payload);    
} 
