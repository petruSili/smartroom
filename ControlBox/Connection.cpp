#include "Connection.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "Configuration.h"
#include "MqttParseAndUpdate.h"

MqttParseAndUpdate* Connection::updateOnReceive = new MqttParseAndUpdate();
char Connection::receivedMessage[512];

void Connection::init(){
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  client.setServer(mqtt_server, 1883);
  client.setBufferSize (512);
  client.setCallback(mqttReceive); 
  client.setKeepAlive(300);
}
void Connection::reConnect(){
  int retry = 0;
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
  
  if(client.connect(mqtt_clientId , mqtt_username, mqtt_password)){
      Serial.println("CONNECTED");
      client.subscribe(deskLamp_statTopic);
      client.subscribe(mainLight_statTopic);
      client.subscribe(arduinoFan_statTopic);
      client.subscribe(powerSave_Topic);
      client.publish(requestUpdate_Topic, "");  //--------- Everytime the system regains connection with the broker it requests to be updated on the state of the devices it controls.
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      retry++;
      // Wait 5 seconds before retrying
      delay(5000);
      if (retry > 5){
        ESP.restart();
      }
    }
  }
}

void Connection::mqttPublish(const char* topic, char* payload){
  client.publish(topic, payload);
}

void Connection::mqttListen(){
  if(!client.connected()){
    reConnect();
  }
  client.loop();
}

/*The following method determines which device the message is destined to and then updates its state*/

void Connection::mqttReceive(char* topic, byte* payload, unsigned int length){
  for (int i=0; i < length; i++) {
    receivedMessage[i] = (char)payload[i];
  }
  if(strcmp(topic,  mainLight_statTopic) == 0){
    updateOnReceive->updateDevice(receivedMessage, mainLight);
    
  }else if(strcmp(topic,  deskLamp_statTopic) == 0){    
    updateOnReceive->updateDeviceExt(receivedMessage, deskLamp);
    
  }else if(strcmp(topic,  arduinoFan_statTopic) == 0){  
    Serial.print("receivedMessage: ");  
    Serial.println(receivedMessage); 
    updateOnReceive->updateDeviceExt(receivedMessage, arduinoFan);
    
  }else if(strcmp(topic,  powerSave_Topic) == 0 ) {    
    updateOnReceive->setPowerSave(receivedMessage);
  }
  memset(receivedMessage, 0, sizeof receivedMessage);
}
