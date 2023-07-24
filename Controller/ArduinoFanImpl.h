/*
 * Class implements a Fan connected to the arduino GPIO but can be controlled externally aswell through MQTT.
 * The MCU sends signals to an ESC to control the BLDC motor.
 */

#ifndef __ARDUINO_FAN_IMPL__
#define __ARDUINO_FAN_IMPL__

#include "DeviceExt.h"
#include "MqttConnection.h"
#include <ServoTimer2.h>

class ArduinoFanImpl:  public DeviceExt { 
public:
  ArduinoFanImpl(MqttConnection* mqttConnection, const char* statTopic, int pin) ;  
  int getState();
  int getIntensity();
  void setIntensity(int i);
  void changeIntensity(int i);
  void setState(int s);
  void switchOn();
  void switchOff(); 
   
private:
  int pin;
  int state;
  int intensity;
  char buffer[10];
  ServoTimer2 escFan;
  const char* statTopic;
  MqttConnection* mqttConnection;
  char payload[50];
  char* generateData();
  void graduallyIncrease(int currentSignal, int newSignal);
  void graduallyDecrease(int currentSignal, int newSignal);
};

#endif
