/* Implementation of temperature and humidity Sensor Interface */

#include "Arduino.h"
#include "TemperatureSensor.h"


void  TemperatureSensor::startSensor(){
  dht.begin();
  }
  
float TemperatureSensor::getTemperature(){
  temp = dht.readTemperature();
  if (!isnan(temp)){
	  return temp;
  }
}

float TemperatureSensor::getHumidity(){
  hum = dht.readHumidity();
  if (!isnan(hum)){
    return hum;
  }
}

float TemperatureSensor::getHeatIndex(){
  heat = dht.computeHeatIndex(temp, hum, false);
  if (!isnan(heat)){ 
    return heat;
  }
}
