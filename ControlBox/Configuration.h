/* An Header File containing configuration data for the ControlBox */

#ifndef __CONFIGURATION__
#define __CONFIGURATION__

#include "Device.h"
#include "DeviceExt.h"

#define ON 1
#define OFF 0

#define MAX_LEVEL 100
#define MIN_LEVEL 0


#define NUM_PINS 34
#define NUM_VARLEVL_DEV 2 //--------------- The length of the circular list of variable intensity devices.
#define DEBOUNCING_TIME 300


#define MAX_EVQUEUE_SIZE 50
#define TIMER_PERIOD 1500 //in miliseconds
#define TIME_TO_SLEEP 180 //in sec

/* Controlled Devices */
#define deskLamp_id 1
#define mainLight_id 2
#define arduinoFan_id 3

/* Touch sensors PIN configuration */
#define TOUCH_SENSOR1_PIN 27
#define TOUCH_SENSOR2_PIN 13
#define TOUCH_SENSOR3_PIN 33
#define TOUCH_THRESHOLD 40

/* Rotary Encoder PIN configuration */
#define ROT_ENC_PIN_CLK 32 
#define ROT_ENC_PIN_DT 21
#define ROT_ENC_PIN_SW 25
#define ROT_ENC_PIN_VCC -1
#define ROT_ENC_STEPS 4 

/* Led Ring configuration */
#define LED_PIN 22 
#define NUM_PIXELS 24
#define BRIGHTNESS 64

/* Events */
#define SENSOR_TOUCHED_EVENT 1
#define STATE_ON_EVENT 2
#define STATE_OFF_EVENT 3
#define NEW_LEVEL_EVENT 4
#define CHANGE_LEVEL_EVENT 5


extern DeviceExt* deskLamp;
extern Device* mainLight;
extern DeviceExt* arduinoFan;


/* PowerSaving configuration  */
extern bool ecoMode;
extern const char* powerSave_Topic;

/* Wifi configuration  */
extern const char* ssid;
extern const char* password;

/* MQTT configuration  */
extern const char* mqtt_clientId;
extern const char* mqtt_server;
extern const char* mqtt_username;
extern const char* mqtt_password;

/* MQTT Command Topic configuration  */
extern const char* mainLight_cmndTopic;     
extern const char* deskLamp_cmndTopic;    
extern const char* arduinoFan_cmndTopic;  
 
/* MQTT State Topic configuration  */
extern const char* requestUpdate_Topic;
extern const char* deskLamp_statTopic; 
extern const char* mainLight_statTopic;
extern const char* arduinoFan_statTopic; 

/* Timer configuration  */
volatile extern bool timeExpired;


#endif
