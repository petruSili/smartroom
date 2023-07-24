/*
 * The following code and the associated files reppresent the implementation of a multi-sensor device
 * capable of detecting motion, temperature and luminosity and send the data over MQTT. 
 * Some of the sensors make use of specific libraries.  The process of retrieving the data and sending it out 
 * was implemented by making use of synchronous tasks managed by a scheduler. 
 * Please note that although the tasks execute according to a timer, 
 * for efficiency reasons tha data is only sent when the current value of a sensor is different from the previous one or the value is positive in case of the PIR sensor. 
 *
 */

#include"Connection.h"
#include"IlluminanceTask.h"
#include"Scheduler.h"
#include"Task.h"
#include"MotionDetectorTask.h"
#include"TemperatureTask.h"
#include"Configuration.h"

/* Wifi configuration  */
const char* ssid = "replaceMe";
const char* password = "replaceMe";

/* MQTT connection configuration  */
const char* mqttClientId = "SensorBox";
const char* mqttServer = "replaceMe";
const char* mqttUsername = "replaceMe";
const char* mqttPassword = "replaceMe";

/* MQTT topic configuration  */
const char* Temperature_statTopic = "sensorbox/TEMPERATURE";
const char* Humidity_statTopic = "sensorbox/HUMIDITY";
const char* HeatIndex_statTopic = "sensorbox/HEATINDEX";
const char* Illuminance_statTopic = "sensorbox/ILLUMINANCE";
const char* isInRoom_statTopic = "sensorbox/MOTIONDETECTED";


Connection* connection;
Scheduler* sched;

Task* sendTemperature;
Task* sendIlluminance;
Task* sendMotion;

void setup() {
  Serial.begin(115200);
  
  connection = new Connection();
  connection->init();
  
  sendTemperature = new TemperatureTask(connection);
  sendTemperature->init(3000);
  sendIlluminance = new IlluminanceTask(connection);
  sendIlluminance->init(500);
  sendMotion = new MotionDetectorTask(connection);
  sendMotion->init(500);
  
  sched = new Scheduler(); 
  sched->init(500);
  sched->addTask(sendTemperature);
  sched->addTask(sendIlluminance);
  sched->addTask(sendMotion);
  
}

void loop() {
  if (!connection->isConnected()) {
    connection->reConnect();
  }
  sched->schedule();
}
