/* An Header File containing configuration data for the BLEScanner */

#ifndef __CONFIGURATION__
#define __CONFIGURATION__

#define UPDATE_PERIOD 180000 // in milliseconds -> 3 min
#define SCAN_TIME 10 // in seconds
#define MIN_RSSI -150

/* Wifi configuration  */
extern const char* ssid;
extern const char* password;

/* MQTT connection configuration  */
extern const char* mqttClientId;
extern const char* mqttServer;
extern const char* mqttUsername;
extern const char* mqttPassword;

#endif
