/* An Header File containing configuration data for the SensorBox */

#ifndef __CONFIGURATION__
#define __CONFIGURATION__


#define PERIOD 500
#define DHTPIN 19 
#define PIRPIN 16  
#define DARK 1 // Value of the illuminance sensor below which the room is DARK

/* Wifi configuration  */
extern const char* ssid;
extern const char* password;

/* MQTT connection configuration  */
extern const char* mqttClientId;
extern const char* mqttServer;
extern const char* mqttUsername;
extern const char* mqttPassword;

/* MQTT topic configuration  */
extern const char* Temperature_statTopic;
extern const char* Humidity_statTopic;
extern const char* HeatIndex_statTopic;
extern const char* Illuminance_statTopic;
extern const char* isInRoom_statTopic;

#endif
