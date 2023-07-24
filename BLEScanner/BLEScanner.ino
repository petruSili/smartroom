/*
 * This is the implementation of a Bluetooth Low Energy Scanner for the Esp32.
 * It uses the BLEDevice.h library and consists in reporting through MQTT the presence of selected BLE capable devices.
 * The WiFi and BLE components are used alternately due to the MCU characteristics.
 */
 
#include "Configuration.h"
#include "Connection.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

/* Wifi configuration  */
const char* ssid = "replaceMe";
const char* password = "replaceMe";

/* MQTT connection configuration  */
const char* mqttClientId = "BLEScanner";
const char* mqttServer = "replaceMe";
const char* mqttUsername = "replaceMe";
const char* mqttPassword = "replaceMe";
const char* isHome_statTopic = "blescanner/isHome";

static BLEAddress *pServerAddress;
BLEScan* pBLEScan;
BLEClient*  pClient;

Connection* wifiMqtt;

bool isHome = true;
bool prevIsHome = isHome;
int doubleCheck = 0;
bool deviceFound = false;
unsigned long lastUpdate;

const char* MiBandAddress = "replaceMe";  //Example:  "e4:82:e5:b0:48:b3"
String knownAddresses[] = {MiBandAddress};

/*Called for each advertising BLE server.
  Checks if any of the found devices corrisponds to the ones in the list of known addresses and
  if the found device is inside the specified range.
*/
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      //Serial.print("BLE Advertised Device found: ");
      //Serial.println(advertisedDevice.toString().c_str());
      pServerAddress = new BLEAddress(advertisedDevice.getAddress());

      bool known = false;
      for (int i = 0; i < (sizeof(knownAddresses) / sizeof(knownAddresses[0])); i++) {
        if (strcmp(pServerAddress->toString().c_str(), knownAddresses[i].c_str()) == 0){   
          known = true;
        }
      }
      if (known) {
        Serial.print("Device found: ");
        Serial.println(advertisedDevice.getRSSI());
        if (advertisedDevice.getRSSI() > MIN_RSSI) deviceFound = true;
        else deviceFound = false;
        Serial.println(pServerAddress->toString().c_str());
        advertisedDevice.getScan()->stop();
      }
    }
}; 

void setup() {
  
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  
  wifiMqtt = new Connection();
  
  BLEDevice::init("");

  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
}

void loop() {

  Serial.println();
  Serial.println("BLE Scan restarted.....");
  deviceFound = false;
  BLEScanResults scanResults = pBLEScan->start(SCAN_TIME);
  if(deviceFound){
    isHome = true;
    doubleCheck = 0;
    Serial.println("is home");
    Serial.println(millis() - lastUpdate);
  }else{
    doubleCheck++;
    if(doubleCheck > 1){  //--------------- The presence is checked twice before setting it to true (false negatives avoidance).
      isHome = false;
      doubleCheck = 0;
    }    
    Serial.println("NOT home");
  }
  
/*The scanner sends an MQTT message if there has been a change in the presence state or every 5 minutes */ 
  if(prevIsHome != isHome || millis() - lastUpdate > UPDATE_PERIOD ){
    
    prevIsHome = isHome;
    wifiMqtt->enableAndConnect();
    wifiMqtt->mqttPublish(isHome_statTopic, "ON");
    Serial.println("published");
    wifiMqtt->disable();  //--------------- The WiFi and Bluetooth work exclusively from eachother.
    btStart(); 
    lastUpdate = millis();
  }  
} 
