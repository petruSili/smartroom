#ifndef __CONNECTION__
#define __CONNECTION__

#include <WiFi.h>
#include <PubSubClient.h>
#include "Configuration.h"


class Connection { 
  
public:

  Connection(): espClient(), client(espClient) {};
  
  void init();
  int isConnected();
  void reConnect();
  void mqttPublish(const char* topic, char* payload);
  
private:
  WiFiClient espClient;
  PubSubClient client;
 
};


#endif
