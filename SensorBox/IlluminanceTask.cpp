#include "IlluminanceTask.h"
#include "IlluminanceSensor.h"
#include "Configuration.h"

IlluminanceTask::IlluminanceTask(Connection* connection){
  this->connection = connection;  
}
  
void IlluminanceTask::init(int period){
  Task::init(period);
  illumSensor = new IlluminanceSensor(); 
  illumSensor->startSensor();
  illuminance = 0;
  newIlluminance = 0;    
}
  
void IlluminanceTask::tick(){
  newIlluminance = illumSensor->getIlluminance();
  if((illuminance > DARK && newIlluminance < DARK) || (illuminance < DARK && newIlluminance > DARK)){
    dtostrf(newIlluminance,3, 2, buffer);
    connection->mqttPublish(Illuminance_statTopic, buffer);
    Serial.println("Illum sent");
    illuminance = newIlluminance;
  }
}
