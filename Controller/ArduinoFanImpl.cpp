#include "ArduinoFanImpl.h"
#include "MqttConnection.h"
#include <ServoTimer2.h>
#include <ArduinoJson.h>

#define MIN_SPEED 1100
#define MAX_SPEED 1250

ArduinoFanImpl::ArduinoFanImpl(MqttConnection* mqttConnection, const char* statTopic, int pin) {
  this->mqttConnection = mqttConnection;
  this->statTopic = statTopic;
  this->pin = pin; 
  intensity = 0;
  state = OFF;
  escFan.attach(pin); //----------------------------------- Initialize the motor.
}

void ArduinoFanImpl::setIntensity(int i){}

int ArduinoFanImpl::getState(){
  return state;
}

int ArduinoFanImpl::getIntensity(){
  return intensity;
}

void ArduinoFanImpl::setState(int s){
  switch(s){
    case ON:
      switchOn(); //--------------------------------------- Since the motor is a component of the controller, when it sets the state it also executes the commands. 
      break;
    case OFF:
      switchOff();  
      break;
  }
}

void ArduinoFanImpl::changeIntensity(int newIntensity){
  int currentSignal;
  int newSignal; 
  if(state == ON){
    if(newIntensity == 0){
      switchOff();
    }else{   
      newSignal = map(newIntensity, 1, 100, MIN_SPEED, MAX_SPEED); //------------------------- Maps the intensity value to the respective motor signal.
      currentSignal = map(intensity, 1, 100, MIN_SPEED, MAX_SPEED);
      
      if(newIntensity > intensity){ 
        graduallyIncrease(currentSignal, newSignal);
      }else if(newIntensity < intensity){
        graduallyDecrease(currentSignal, newSignal);
      }      
    }
  }
  intensity = newIntensity;
  mqttConnection->clientPublish(arduinoFan_statTopic, generateData());                                    
}  

void ArduinoFanImpl::switchOn(){
  Serial.println(F("switchOn()"));
  escFan.write(MIN_SPEED);
  if(intensity > 0){
    graduallyIncrease(MIN_SPEED, map(intensity, 1, 100, MIN_SPEED, MAX_SPEED));
  }
  state = ON;
  mqttConnection->clientPublish(arduinoFan_statTopic, generateData()); 
  Serial.println(generateData());
}

void ArduinoFanImpl::switchOff(){
  escFan.write(0);
  state = OFF;
  mqttConnection->clientPublish(arduinoFan_statTopic, generateData());  
  Serial.println(generateData());
}

/*arduinoFan must announce it's state every time it's been changed*/
char* ArduinoFanImpl::generateData(){
  StaticJsonDocument<256> doc;
  if(state == ON){
    doc["POWER"] = "ON";
  }else{
    doc["POWER"] = "OFF";
  } 
  doc["Dimmer"] = intensity;
  memset(payload, 0, sizeof payload);
  serializeJson(doc, payload); 
  return payload;
}

void ArduinoFanImpl::graduallyIncrease(int currentSignal, int newSignal){
  for(currentSignal; currentSignal<=newSignal; currentSignal+=5){ //-------------- The speed of the motor increases gradually.
    escFan.write(currentSignal);
    delay(50);
    }
}

void ArduinoFanImpl::graduallyDecrease(int currentSignal, int newSignal){
  for(currentSignal; currentSignal>=newSignal; currentSignal-=5){ //-------------- The speed of the motor increases gradually.
    escFan.write(currentSignal);
    delay(50);
    }
}
