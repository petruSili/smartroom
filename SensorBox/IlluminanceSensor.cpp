#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include "IlluminanceSensor.h"

float IlluminanceSensor::getIlluminance(){
  /* Get a new sensor event */ 
  sensors_event_t event;
  tsl.getEvent(&event);
 
  /* If event.light = 0 lux the sensor is probably saturated */
    /* and no reliable data could be generated! */
    /* if event.light is +/- 4294967040 there was a float over/underflow */
  if ((event.light == 0) |
      (event.light > 4294966000.0) | 
      (event.light <-4294966000.0))
  {
  
    Serial.println(F("Invalid data (adjust gain or timing)"));
  }
  else
  {
    return event.light;
  }
}


void IlluminanceSensor::startSensor()
{
  tsl.setGain(TSL2591_GAIN_MED);      
  tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);

}
