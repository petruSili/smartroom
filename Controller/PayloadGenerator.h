#ifndef __JSON_GENERATOR__
#define __JSON_GENERATOR__

#include <ArduinoJson.h>
#include"Configuration.h"

class PayloadGenerator {
  
public: 
  PayloadGenerator();  
  char* getDeviceState(Device* device);
  char* getDeviceExtState(DeviceExt* device);
  
   
private:
  char payload[50];

};


#endif
