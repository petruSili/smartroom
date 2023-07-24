#ifndef __MQTT_CONNECTION__
#define __MQTT_CONNECTION__

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "Configuration.h"
#include "PayloadParser.h"
#include "PayloadGenerator.h"


class MqttConnection { 
  
public:
  
  MqttConnection(): ethClient(), mqttClient(ethClient), ip(ipAddr){};
  
  void init();
  void clientReconnect();
  void clientPublish(const char* topic, char* payload);
  void clientListen();
  void clientSendStats();
  
  static PayloadParser* payloadParser;
  static PayloadGenerator* payloadGenerator;
  static char receivedMessage[512];
  
private:
  EthernetClient ethClient;
  PubSubClient mqttClient;
  IPAddress ip;
  
  static void mqttReceive(char* topic, byte* payload, unsigned int length);
};


#endif
