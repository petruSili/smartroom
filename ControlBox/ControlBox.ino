/*
 *The following code is the implementation of a physical control panel
 *that keeps track of the states of 3 devices and controls them using:
 *  - 3 Capacitive Touch Sensors: ON/OFF
 *  - 1 Rotary Encoder + Switch: select Device and set INTENSITY
 *  - 1 LED ring for visual feedback  
 *The system is event based.
 *The AsyncFSMs that represent the controlled devices share a single queue of events and handle them accordingly.
*/




#include "Configuration.h"
#include "LedRing.h"
#include "Device.h"
#include "Connection.h"
#include "Input.h"
#include "TouchInput.h"
#include "ButtonInput.h"
#include "MqttDeviceImpl.h"
#include "MqttDeviceExtImpl.h"
#include "Arduino.h"
#include "Timer.h"
#include "SmartRoomAsyncFSM.h"
#include "SmartRoomExtAsyncFSM.h"
#include "MqttParseAndUpdate.h"
#include "RotaryEncoder.h"
#include "PowerSaving.h"

/* PowerSaving configuration  */
bool ecoMode = false;

/* Wifi configuration  */
const char* ssid = "replaceMe";
const char* password = "replaceMe";

/* MQTT configuration  */
const char* mqtt_clientId = "ControlBox";
const char* mqtt_server = "replaceMe";
const char* mqtt_username = "replaceMe";
const char* mqtt_password = "replaceMe";

/* MQTT Command Topic configuration  */
const char* deskLamp_cmndTopic = "cmnd/deskLamp";  
const char* mainLight_cmndTopic = "cmnd/mainLight"; 
const char* arduinoFan_cmndTopic = "cmnd/arduinoFan";
 
/* MQTT State Topic configuration  */
const char* powerSave_Topic = "stat/ecoMode"; 
const char* requestUpdate_Topic = "update/Request";

const char* deskLamp_statTopic = "stat/deskLamp/RESULT"; 
const char* mainLight_statTopic = "stat/mainLight/RESULT"; 
const char* arduinoFan_statTopic = "stat/arduinoFan/RESULT"; 

 
volatile bool timeExpired = true;

int variableIntensityDevices[NUM_VARLEVL_DEV] = {deskLamp_id, arduinoFan_id};


Connection* connection;
Timer* timer;
PowerSaving* power;

/* Inputs/event sources*/
TouchInput* padDeskLamp;
TouchInput* padMainLight;
TouchInput* padFan;
ButtonInput* deviceSelector;
RotaryEncoder* rotaryEncoder;

LedRing* ledRing; 


DeviceExt* deskLamp;
Device* mainLight;
DeviceExt* arduinoFan;

SmartRoomAsyncFSM* mainLightAsyncFSM;
SmartRoomExtAsyncFSM* deskLampAsyncFSM;
SmartRoomExtAsyncFSM* arduinoFanAsyncFSM;

void setup() {
  Serial.begin(115200);
  delay(1000); 
  connection = new Connection();
  
  timer = new Timer(TIMER_PERIOD);
  ledRing = new LedRing(LED_PIN);
  rotaryEncoder = new RotaryEncoder();
 
  deskLamp = new MqttDeviceExtImpl(connection, deskLamp_cmndTopic, deskLamp_id);
  mainLight = new MqttDeviceImpl(connection, mainLight_cmndTopic, mainLight_id);
  arduinoFan = new MqttDeviceExtImpl(connection, arduinoFan_cmndTopic, arduinoFan_id);

  padDeskLamp = new TouchInput(TOUCH_SENSOR1_PIN);
  padMainLight = new TouchInput(TOUCH_SENSOR2_PIN);
  padFan = new TouchInput(TOUCH_SENSOR3_PIN);
  deviceSelector = new ButtonInput(ROT_ENC_PIN_SW, variableIntensityDevices);
  
  mainLightAsyncFSM = new SmartRoomAsyncFSM(padMainLight, mainLight, ledRing);
  deskLampAsyncFSM = new SmartRoomExtAsyncFSM(padDeskLamp, deskLamp, deviceSelector, timer, ledRing, rotaryEncoder);
  arduinoFanAsyncFSM = new SmartRoomExtAsyncFSM(padFan, arduinoFan, deviceSelector, timer, ledRing, rotaryEncoder);

  connection->init();
  ledRing->init();
  rotaryEncoder->init();
  timer->init();
}

void loop() {
  connection->mqttListen();
  arduinoFanAsyncFSM->checkEvents();
  mainLightAsyncFSM->checkEvents();  
  deskLampAsyncFSM->checkEvents();
  if(ecoMode){power->sleepMode();}
}
