#include "MqttConnection.h"
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "Configuration.h"

char MqttConnection::receivedMessage[512];
PayloadParser* MqttConnection::payloadParser = new PayloadParser();
PayloadGenerator* MqttConnection::payloadGenerator = new PayloadGenerator();


void MqttConnection::init(){
  Ethernet.begin(macAddr, ipAddr);   
  delay(2000);
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setBufferSize (512);
  mqttClient.setCallback(mqttReceive); 
  mqttClient.setKeepAlive(300);
}

void MqttConnection::clientReconnect(){
  int retry = 0;
  while (!mqttClient.connected()) {
    Serial.println(F("Attempting MQTT connection..."));  
    if(mqttClient.connect(mqtt_clientId , mqtt_username, mqtt_password)){
        Serial.println(F("CONNECTED"));      
        mqttClient.subscribe(deskLamp_statTopic); //----------------------- Controller connects to all these topics to traack their states
        mqttClient.subscribe(mainLight_statTopic);
        mqttClient.subscribe(nightLamps_statTopic);
        mqttClient.subscribe(arduinoFan_powerCmndTopic);
        mqttClient.subscribe(arduinoFan_intensityCmndTopic);
        mqttClient.subscribe(isHome_statTopic);
        mqttClient.subscribe(isInRoom_statTopic);
        mqttClient.subscribe(Temperature_statTopic);
        mqttClient.subscribe(Humidity_statTopic);
        mqttClient.subscribe(HeatIndex_statTopic);
        mqttClient.subscribe(Illuminance_statTopic); 
        mqttClient.subscribe(requestUpdate_Topic);     
    }else{
        Serial.print(F("failed, rc="));
        Serial.print(mqttClient.state());
        Serial.println(F(" try again in 5 seconds"));
        retry++;
        Serial.print(retry);
        delay(5000); //--------------------------------------------------- Wait 5 seconds before retrying
    }
  }
}

void MqttConnection::clientPublish(const char* topic, char* payload){
   mqttClient.publish(topic, payload);
}

void MqttConnection::clientListen(){
  if(! mqttClient.connected()){
    clientReconnect();
  }
  mqttClient.loop();
}

/*
 * The following method is called every time an MQTT message is received
 */
void MqttConnection::mqttReceive(char* topic, byte* payload, unsigned int length){
  for(int i=0; i < length; i++){
    receivedMessage[i] = (char)payload[i];
  }
  if(strcmp(topic, requestUpdate_Topic) == 0){ 
    mqttUpdateRequested = true;
        
  }else if(strcmp(topic, isHome_statTopic) == 0){
    isHome = payloadParser->parseHomePresence(receivedMessage);
    lastTimeHome = millis();
       
  }else if(strcmp(topic, isInRoom_statTopic) == 0) {;
    isInRoom = payloadParser->parseRoomPresence(receivedMessage);
    lastTimeInRoom = millis();
       
  }else if(strcmp(topic, Temperature_statTopic) == 0) {
    Temperature = payloadParser->parseRoomTemperature(receivedMessage);
   
    
  }else if(strcmp(topic, Humidity_statTopic) == 0) {
    Humidity = payloadParser->parseRoomHumidity(receivedMessage);
     
     
  }else if(strcmp(topic, HeatIndex_statTopic) == 0) { //---------------------------- Sets the state for the cooling.
    HeatIndex = payloadParser->parseRoomHeatIndex(receivedMessage);
    if(HeatIndex < HEATINDEX_COOL){
      roomCoolingState = COOL;
    }else if(HeatIndex > HEATINDEX_COOL && HeatIndex < HEATINDEX_WARM){
      roomCoolingState = WARM;
    }else if(HeatIndex > HEATINDEX_WARM && HeatIndex < HEATINDEX_HOT){
      roomCoolingState = HOT;
    }else if(HeatIndex > HEATINDEX_HOT && HeatIndex < HEATINDEX_VERY_HOT){
      roomCoolingState = VERY_HOT;
    }
    
  }else if(strcmp(topic, Illuminance_statTopic) == 0) { //---------------------------- Sets the state for the illuminance.
    Illuminance = payloadParser->parseRoomIlluminance(receivedMessage);
    if(Illuminance > ILLUM_THRESHOLD){
      roomIlluminanceState = BRIGHT;
    }else{
      roomIlluminanceState = DARK;
    }  
    
  }else if(strcmp(topic, arduinoFan_powerCmndTopic) == 0) { //------------------------ Receives ON/OFF command and executes it.
    arduinoFan->setState(payloadParser->parsePowerCmnd(receivedMessage));
    
  }else if(strcmp(topic, arduinoFan_intensityCmndTopic) == 0) { //-------------------- Receives the INTENSITY command and executes it.
    arduinoFan->changeIntensity(payloadParser->parseIntensityCmnd(receivedMessage));
    
  }else  if(strcmp(topic, deskLamp_statTopic) == 0) { //------------------------------ Receives ON/OFF state update from device.
    deskLamp->setState(payloadParser->parsePowerStat(receivedMessage));
    if(payloadParser->parseIntensityStat(receivedMessage) != -1){ //------------------ Checks if the payload contains INTENSITY state.
      deskLamp->setIntensity(payloadParser->parseIntensityStat(receivedMessage));
    }
      
  }else if(strcmp(topic, mainLight_statTopic) == 0) { //------------------------------ Receives ON/OFF state update from device.
    mainLight->setState(payloadParser->parsePowerStat(receivedMessage));  
    
  }else if(strcmp(topic, nightLamps_statTopic) == 0) { //------------------------------ Receives ON/OFF state update from device.
    nightLamps->setState(payloadParser->parsePowerStat(receivedMessage));  
  }  
  memset(receivedMessage, 0, sizeof receivedMessage);     
}

/*Sends state update*/
void MqttConnection::clientSendStats(){
  mqttClient.publish(mainLight_statTopic, payloadGenerator->getDeviceState(mainLight));
  mqttClient.publish(deskLamp_statTopic, payloadGenerator->getDeviceState(deskLamp));
  mqttClient.publish(arduinoFan_statTopic, payloadGenerator->getDeviceState(arduinoFan));
  if(isHome){
    mqttClient.publish(powerSave_statTopic, "OFF");
  }else{
    mqttClient.publish(powerSave_statTopic, "ON");
  }
  mqttUpdateRequested = false;
}
