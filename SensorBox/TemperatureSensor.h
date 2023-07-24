/* A Basic interface modelling a temperature and humidity Sensor */
#ifndef __TEMPERATURESENSOR__
#define __TEMPERATURESENSOR__

#include"DHT.h"
#include "TemperatureSensor.h"

class TemperatureSensor {
	
public: 
	TemperatureSensor(int dhtPin): dht(dhtPin, DHT22){};  
  void  startSensor();
	float getTemperature();
  float getHumidity();
  float getHeatIndex();
	
private:
	float temp;
  float hum;
  float heat;  
  DHT dht;    
};

#endif
