#include "TemperatureTask.h"
#include "Configuration.h"
#include "TemperatureSensor.h"

TemperatureTask::TemperatureTask(Connection* connection){
  this->connection = connection;   
}
  
void TemperatureTask::init(int period){
  Task::init(period);
  tempSensor = new TemperatureSensor(DHTPIN); 
  tempSensor->startSensor();
  temperature = 0;
  humidity = 0;
  heatIndex = 0;
  newTemperature = 0;
  newHumidity = 0;
  newHeatIndex = 0;    
}
  
void TemperatureTask::tick(){
  newTemperature = tempSensor->getTemperature();
  if(newTemperature != temperature){
    dtostrf(newTemperature,3, 1, buffer);
    connection->mqttPublish(Temperature_statTopic, buffer);
    Serial.println("Temp sent");
    temperature = newTemperature;
  }
  newHumidity = tempSensor->getHumidity();
  if(newHumidity != humidity){
    dtostrf(newHumidity,3, 1, buffer);
    connection->mqttPublish(Humidity_statTopic, buffer);
    humidity = newHumidity;
  }
  newHeatIndex = tempSensor->getHeatIndex();
  if(newHeatIndex != heatIndex){
    dtostrf(newHeatIndex,3, 1, buffer);
    connection->mqttPublish(HeatIndex_statTopic, buffer);
    heatIndex = newHeatIndex;
  }
}
