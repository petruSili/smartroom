 /* An Header File containing configuration data for the ControlBox */

#ifndef __CONFIGURATION__
#define __CONFIGURATION__

#include <Arduino.h>
#include "Device.h"
#include "DeviceExt.h"

#define OFF 0
#define ON 1
#define FAN_PIN 4
#define NUM_DEVICES 4

#define deskLamp_ID 0
#define mainLight_ID 1
#define arduinoFan_ID 2
#define nightLamps_ID 3
#define isAuto_ID 4
#define isAsleep_ID 5

/* Fan Speed configuration  */
#define WARM_SPEED 30
#define HOT_SPEED 60
#define VERY_HOT_SPEED 100

#define ILLUM_THRESHOLD 1 //value that disinguishes between the DARK and BRIGHT illuminance states

#define HEATINDEX_COOL 25
#define HEATINDEX_WARM 27
#define HEATINDEX_HOT 30
#define HEATINDEX_VERY_HOT 33

#define IS_HOME_INTERVAL 600000 // 10 min
#define IS_INROOM_INTERVAL 600000 // 10 min
#define NIGHT_COOLING_TIME 180000 //3 min
#define NIGHT_LIGHT_TIME 180000 //3 min


#define NIGHT_LIGHT_TIME 180000 //3 min

/* Wifi configuration  */
extern const uint8_t macAddr[];
extern const uint8_t ipAddr[];

/* MQTT configuration  */
extern const char* mqtt_clientId;
extern const char* mqtt_server;
extern const char* mqtt_username;
extern const char* mqtt_password;

/* MQTT Command Topic configuration  */
extern const char* mainLight_cmndTopic;     
extern const char* deskLamp_cmndTopic; 
extern const char* nightLamps_cmndTopic;  
extern const char*  arduinoFan_powerCmndTopic;  
extern const char* arduinoFan_intensityCmndTopic; 

/* MQTT Receive Device State Topic configuration  */
extern const char* deskLamp_statTopic; 
extern const char* mainLight_statTopic; 
extern const char* nightLamps_statTopic;
extern const char* arduinoFan_statTopic; 

/* MQTT Device State Topic configuration  */
extern const char* deskLamp_sendStateTopic; 
extern const char* mainLight_sendStateTopic; 
extern const char* nightLamps_statTopic;
extern const char* arduinoFan_statTopic;
extern const char* requestUpdate_Topic;
extern const char* powerSave_statTopic;
extern const char* isHome_statTopic;
extern const char* isInRoom_statTopic;
extern const char* Temperature_statTopic;
extern const char* Humidity_statTopic;
extern const char* HeatIndex_statTopic;
extern const char* Illuminance_statTopic;

extern Device* nightLamps;
extern Device* mainLight;
extern DeviceExt* deskLamp;
extern DeviceExt* arduinoFan;

/*Room Illuminance config*/

enum IlluminanceState { BRIGHT, DARK };
extern IlluminanceState roomIlluminanceState;



enum  CoolingState { COOL, WARM, HOT, VERY_HOT };
extern  CoolingState roomCoolingState;

extern int isAuto;
extern bool isInRoom;
extern long lastTimeInRoom;
extern long lastDetectedMotion;
extern bool isHome;
extern long lastTimeHome;
extern int isAsleep;
extern bool mqttUpdateRequested;
extern bool httpUpdateRequested;

extern double Temperature;
extern double Humidity;
extern double HeatIndex;
extern double Illuminance;



#endif
