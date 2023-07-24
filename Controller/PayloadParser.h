#ifndef __PAYLOAD_PARSER__
#define __PAYLOAD_PARSER__

#include <ArduinoJson.h>
#include"Configuration.h"

class PayloadParser {
  
public: 
  PayloadParser();  
  int parseDeviceId( char* payload);
  int parsePowerStat( char* payload);
  int parseIntensityStat( char* payload);
  int parsePowerCmnd( char* payload);
  int parseIntensityCmnd( char* payload);
  bool parseHomePresence(char* payload);
  bool parseRoomPresence(char* payload);
  double parseRoomIlluminance(char* payload);
  double parseRoomTemperature(char* payload);
  double parseRoomHumidity(char* payload);
  double parseRoomHeatIndex(char* payload);
  int parseMode(char* payload);

   
private:
  

};


#endif
