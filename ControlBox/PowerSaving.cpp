#include "PowerSaving.h"
#include "Connection.h"
#include "Configuration.h"

#define uS_TO_S_FACTOR 1000000ULL

PowerSaving::PowerSaving(Connection* connection, const char* presenceTopic){
  this->connection = connection;
  this->presenceTopic = presenceTopic; 
}
       
void PowerSaving::sleepMode(){
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();      
}

void PowerSaving::askPresenceUpdate(){
    connection->mqttPublish(presenceTopic, "UPDATE");    
}
