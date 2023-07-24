#include "Connection.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "Configuration.h"

void Connection::enableAndConnect(){ 
  unsigned long entry;
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  entry = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - entry >= 3000){
      esp_restart();
    }
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
  mqttClient.setServer(mqttServer, 1883);
  mqttClient.setBufferSize(64);
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
}

void Connection::disable(){ 
  mqttClient.disconnect();
  delay(100);
  WiFi.mode(WIFI_OFF);
}
void Connection::mqttPublish(const char* topic, char* payload){
  mqttClient.publish(topic, payload);
}
