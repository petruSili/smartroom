#ifndef __CONNECTION__
#define __CONNECTION__

#include <WiFi.h>
#include <PubSubClient.h>
#include "Configuration.h"
#include "MqttParseAndUpdate.h"

class Connection { 
  
public:

  Connection(): espClient(), client(espClient) {};
  
  void init();
  void reConnect();
  void mqttPublish(const char* topic, char* payload);
  void mqttListen();
  
  static MqttParseAndUpdate* updateOnReceive;
  static char receivedMessage[512];
  
private:
  WiFiClient espClient;
  PubSubClient client;
 
  static void mqttReceive(char* topic, byte* payload, unsigned int length);
};


#endif
