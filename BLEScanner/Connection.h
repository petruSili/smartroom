#ifndef __CONNECTION__
#define __CONNECTION__

#include <WiFi.h>
#include <PubSubClient.h>
#include "Configuration.h"


class Connection { 
  
public:

  Connection(): espClient(), mqttClient(espClient) {};
  
  void enableAndConnect();
  void disable();
  
  void mqttPublish(const char* topic, char* payload);
  
private:
  WiFiClient espClient;
  PubSubClient mqttClient;
  int isConnected();
  void reConnect();
 
};


#endif
