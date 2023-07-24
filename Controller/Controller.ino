/*
 * The code implements the controller of a "SmartRoom" system.
 * The following are its functions:
 * - retrieve sensor and device state data through MQTT
 * - implement an HTTP server for the mobile app
 * - send sensor and device data to other entities when requested
 * - implement a system to automatically manage the smart devices
 */
 
#include "Configuration.h"
#include "HttpConnection.h"
#include "MqttConnection.h"
#include "ArduinoFanImpl.h"
#include "MqttDeviceImpl.h"
#include "MqttDeviceExtImpl.h"
#include "Scheduler.h"
#include "CoolingTask.h"
#include "HomePresenceTask.h"
#include "RoomPresenceTask.h"
#include "TurnOffDevicesTask.h"
#include "AwakeIlluminanceTask.h"
#include "AsleepIlluminanceTask.h"

int isAuto = OFF;
bool isHome = true;
bool isInRoom = true;
int isAsleep = OFF;

double Temperature;
double Humidity;
double HeatIndex;
double Illuminance;

long lastTimeInRoom = 0;
long lastTimeHome = 0;
long lastDetectedMotion = 0;

bool mqttUpdateRequested = false;
bool httpUpdateRequested = false;

const uint8_t macAddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
const uint8_t ipAddr[] = {replaceMe};

/* MQTT configuration */
const char* mqtt_clientId = "ArduinoController";
const char* mqtt_server = "replaceMe";
const char* mqtt_username = "replaceMe";
const char* mqtt_password = "replaceMe";

/* MQTT Command Topic configuration */
const char* deskLamp_cmndTopic = "cmnd/deskLamp";  
const char* mainLight_cmndTopic = "cmnd/mainLight"; 
const char* nightLamps_cmndTopic = "cmnd/nightLamps";
const char* arduinoFan_powerCmndTopic = "cmnd/arduinoFan/POWER";  //--------- arduino directly controls the Fan, it's an internal component
const char* arduinoFan_intensityCmndTopic = "cmnd/arduinoFan/Dimmer";

/* MQTT Receive Device Data Topic configuration */
const char* deskLamp_statTopic = "stat/deskLamp/RESULT"; 
const char* mainLight_statTopic = "stat/mainLight/RESULT"; 
const char* nightLamps_statTopic = "stat/nightLamps/RESULT";
const char* arduinoFan_statTopic = "stat/arduinoFan/RESULT";

/* MQTT Send Device Data Topic configuration */
const char* requestUpdate_Topic = "update/Request";
const char* powerSave_statTopic = "stat/ecoMode/RESULT";

/* MQTT Receive Sensor Data Topic configuration */
const char* isHome_statTopic = "blescanner/isHome";
const char* isInRoom_statTopic = "sensorbox/MOTIONDETECTED";
const char* Temperature_statTopic = "sensorbox/TEMPERATURE";
const char* Humidity_statTopic = "sensorbox/HUMIDITY";
const char* HeatIndex_statTopic = "sensorbox/HEATINDEX";
const char* Illuminance_statTopic = "sensorbox/ILLUMINANCE";
 

IlluminanceState roomIlluminanceState;
CoolingState roomCoolingState;

MqttConnection* mqttConnection;
HttpConnection* httpConnection;

Device* allDevices[NUM_DEVICES];
Device* mainLight;
Device* nightLamps;
DeviceExt* deskLamp;
DeviceExt* arduinoFan;

Scheduler* sched;
Task* awakeLightManagement;  
Task* asleepLightManagement;
Task* coolingManagement;
Task* homePresence;
Task* roomPresence;
Task* devicesOff;

void setup() {
  
  Serial.begin(9600);
  delay(1000);

  sched = new Scheduler();
   
  mqttConnection = new MqttConnection();
  httpConnection = new HttpConnection();
  
  arduinoFan =  new ArduinoFanImpl(mqttConnection,  arduinoFan_powerCmndTopic, FAN_PIN);
  mainLight = new MqttDeviceImpl(mqttConnection, mainLight_cmndTopic);
  nightLamps = new MqttDeviceImpl(mqttConnection, nightLamps_cmndTopic);
  deskLamp = new MqttDeviceExtImpl(mqttConnection, deskLamp_cmndTopic);
  
  allDevices[deskLamp_ID] = deskLamp;
  allDevices[mainLight_ID] = mainLight;
  allDevices[arduinoFan_ID] = arduinoFan;
  allDevices[nightLamps_ID] = nightLamps;
  
  sched->init(100);
  
  mqttConnection->init();
  httpConnection->init();
  
  awakeLightManagement = new AwakeIlluminanceTask(nightLamps);
  awakeLightManagement->init(500);
  asleepLightManagement = new AsleepIlluminanceTask(nightLamps);
  asleepLightManagement->init(500); 
  coolingManagement = new CoolingTask(arduinoFan);
  coolingManagement->init(500);
  homePresence = new HomePresenceTask();
  homePresence->init(500);
  roomPresence = new RoomPresenceTask();
  roomPresence->init(500);
  devicesOff = new TurnOffDevicesTask(allDevices);
  devicesOff->init(500);
  
  sched->addHomeTask(homePresence);
   
  sched->addAwayTask(homePresence);
  
  sched->addAwayTask(devicesOff);

  sched->addInRoomTask(roomPresence);
  
  sched->addNotInRoomTask(devicesOff);
  sched->addNotInRoomTask(roomPresence);
  
  sched->addAwakeTask(awakeLightManagement);
  sched->addAwakeTask(coolingManagement);

  sched->addAsleepTask(devicesOff);
  sched->addAsleepTask(asleepLightManagement);
  sched->addAsleepTask(coolingManagement); 
  
}

void loop() {

  mqttConnection->clientListen();
  if(mqttUpdateRequested) mqttConnection->clientSendStats();
  httpConnection->serverListen();
  if(isAuto) sched->schedule(); //------ isAuto defines how the user wants to control the devices (automatically or manually)
}
