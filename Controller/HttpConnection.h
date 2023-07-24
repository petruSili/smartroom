#ifndef __HTTP_CONNECTION__
#define __HTTP_CONNECTION__

#include <SPI.h>
#include <Ethernet.h>
#include "Configuration.h"
#include "PayloadParser.h"

class HttpConnection { 
  
public:

  HttpConnection() : httpClient(), httpServer(80), ip(ipAddr){};
  
  void init();
  void serverListen();
  
  static PayloadParser* payloadParser;
  static char httpBody[512];
  static char httpHeader[512];
  
  
private: 
  EthernetClient httpClient;
  EthernetServer httpServer;
  IPAddress ip;
  
  void sendData();
  int getContentLength(char* httpHeader);
  void parseExecCmnds(char* httpContent);
};


#endif
