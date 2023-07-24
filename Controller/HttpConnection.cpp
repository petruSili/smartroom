#include "HttpConnection.h"
#include <SPI.h>
#include <Ethernet.h>
#include "Configuration.h"
#include "PayloadParser.h"
#include <ArduinoJson.h>

char HttpConnection::httpBody[512];
char HttpConnection::httpHeader[512];
PayloadParser* HttpConnection::payloadParser = new PayloadParser();

void HttpConnection::init(){
  Ethernet.begin(macAddr, ipAddr);   
  delay(1000);
  httpServer.begin();
  Serial.print(F("HTTP server is at: "));
  Serial.println(Ethernet.localIP());
}

void HttpConnection::serverListen(){
  int index = 0;
  httpClient = httpServer.available();
  if(httpClient){
    Serial.println("Client");   
    boolean currentLineIsBlank = true; //-------------------- An http request ends with a blank line.
    while(httpClient.connected()){
      while(httpClient.available()){
        char c = httpClient.read();
        httpHeader[index] = c;
        index++;                                                
        if (c == '\n' && currentLineIsBlank) {  //----------- If you've gotten to the end of the line and the line is blank, the http request has ended.                                                 
          if(getContentLength(httpHeader) > 0){ //----------- If the body is NOT empty then it is a POST request. 
            index = 0;
            while(httpClient.available()){
              httpBody[index] = httpClient.read();
              index++;
            } 
            Serial.print("Body: ");
            Serial.println(httpBody);
            httpClient.println(F("HTTP/1.0 200 OK"));
            parseExecCmnds(httpBody); //---------------------- Parses the payload.        
          }else if(getContentLength(httpHeader) == 0){  //---- If the body is empty then it is a GET request.           
            httpClient.println(F("HTTP/1.0 200 OK"));
            httpClient.println(F("Content-Type: application/json"));
            httpClient.println(F("Connection: close"));
            httpClient.print(F("Content-Length: "));     
            sendData(); //------------------------------------ Constructs the payload in Json format and sends it.
          }  
          memset(httpHeader, 0, sizeof httpHeader); 
          memset(httpBody, 0, sizeof httpBody);       
          httpClient.stop();
        }
        else if (c == '\n') {
          currentLineIsBlank = true;  //----------------------- You're starting a new line.
        } 
        else if (c != '\r') {
          currentLineIsBlank = false; //----------------------- You've gotten a character on the current line.
        }
      }
    }
    Serial.println("Disconnected");
  }
}
 
int HttpConnection::getContentLength(char* httpHeader){
  char *pch;
  char numStr[10];
  int index = 0;
  pch = strstr (httpHeader, "Content-Length: ");
  if (pch != NULL)
    pch = pch + strlen("Content-Length: ")*sizeof(char);
    while(isdigit(*pch)){
        numStr[index] = *pch;
        pch += sizeof(char);
        index++;
    }
  return atoi(numStr);  
}

/*Sends a Json containing the states of devices and sensors to the mobile app*/
void HttpConnection::sendData(){   
  StaticJsonDocument<256> doc;
  doc["stats"]["mainLight"]["POWER"] = mainLight->getState();
  doc["stats"]["deskLamp"]["POWER"] = deskLamp->getState();
  doc["stats"]["deskLamp"]["Dimmer"] = deskLamp->getIntensity();
  doc["stats"]["arduinoFan"]["POWER"] = arduinoFan->getState();
  doc["stats"]["arduinoFan"]["Dimmer"] = arduinoFan->getIntensity();
  doc["stats"]["temperature"] = Temperature;
  doc["stats"]["humidity"] = Humidity;
  doc["stats"]["autoMode"]["POWER"] = isAuto;
  doc["stats"]["sleeping"]["POWER"] = isAsleep;
  httpClient.println(measureJson(doc));
  httpClient.println();
  serializeJson(doc, httpClient);
}

/*Receives commands in Json from mobile app and executes them*/
void HttpConnection::parseExecCmnds(char* httpContent){
  switch(payloadParser->parseDeviceId(httpContent)){
    case deskLamp_ID:
      if(payloadParser->parsePowerStat(httpContent) == ON){
        deskLamp->switchOn();
      }else if (payloadParser->parsePowerStat(httpContent) == OFF){
        deskLamp->switchOff();        
      }
      if(payloadParser->parseIntensityStat(httpContent) != -1){
        deskLamp->changeIntensity(payloadParser->parseIntensityStat(httpContent));      
      }     
      break;
    case mainLight_ID:
      if(payloadParser->parsePowerStat(httpContent) == ON){
        mainLight->switchOn();
      }else if (payloadParser->parsePowerStat(httpContent) == OFF){
        mainLight->switchOff();        
      }
      break;
    case arduinoFan_ID:
      if(payloadParser->parsePowerStat(httpContent) == ON){
        arduinoFan->switchOn();
      }else if (payloadParser->parsePowerStat(httpContent) == OFF){
        arduinoFan->switchOff();        
      }
      if(payloadParser->parseIntensityStat(httpContent) != -1){
        arduinoFan->changeIntensity(payloadParser->parseIntensityStat(httpContent));      
      }
      break; 
    case isAuto_ID:
      isAuto = payloadParser->parsePowerStat(httpContent);
      if(isAuto == OFF){ //--------------------------------- Sleeping mode can only be enabled when Auto mode is enabled.
        isAsleep = OFF;
        }
      break; 
    case isAsleep_ID:
      isAsleep = payloadParser->parsePowerStat(httpContent);
      break;      
  }  
}
