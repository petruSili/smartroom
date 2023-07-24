#include "Connection.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "Configuration.h"

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
  
  client.setServer(mqttServer, 1883);
  client.setBufferSize (512);
  client.setKeepAlive(300);
}
int Connection::isConnected(){
  return client.connected();
}

void Connection::reConnect(){
  int retry = 0;
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
  
  if(client.connect(mqttClientId , mqttUsername, mqttPassword)){
      Serial.println("CONNECTED");
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
