#include "Arduino.h"
#include "PirSensor.h"

PirSensor::PirSensor(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);     
} 
  
bool PirSensor::isDetected(){
  return digitalRead(pin) ? true : false;
}
