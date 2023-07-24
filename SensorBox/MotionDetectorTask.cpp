#include "MotionDetectorTask.h"
#include "Configuration.h"
#include "PirSensor.h"

MotionDetectorTask::MotionDetectorTask(Connection* connection){
  this->connection = connection;   
}
  
void MotionDetectorTask::init(int period){
  Task::init(period);
  pirSensor = new PirSensor(PIRPIN);   
}
  
void MotionDetectorTask::tick(){
  if(pirSensor->isDetected()){
      connection->mqttPublish(isInRoom_statTopic, "ON");
      Serial.println("Motion sent");
  } 
}
