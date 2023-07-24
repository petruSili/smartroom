#include "async_fsm.h"
#include "Arduino.h"
#include "Configuration.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "RotaryEncoder.h"

/* ------------------------ InterruptDispatcher ----------- */

/* The singleton interrupt dispatcher, binding interrupts to event sources */

InterruptDispatcher interruptDispatcher;

/* 
 * Functions called by the interrupt handlers, used to notify interrupts to
 * to the interrupt dispatcher
 */
void notifyInterrupt_0(){ interruptDispatcher.notifyInterrupt(0); }
void notifyInterrupt_1(){ interruptDispatcher.notifyInterrupt(1); }
void notifyInterrupt_2(){ interruptDispatcher.notifyInterrupt(2); }
void notifyInterrupt_3(){ interruptDispatcher.notifyInterrupt(3); }
void notifyInterrupt_4(){ interruptDispatcher.notifyInterrupt(4); }
void notifyInterrupt_5(){ interruptDispatcher.notifyInterrupt(5); }
void notifyInterrupt_6(){ interruptDispatcher.notifyInterrupt(6); }
void notifyInterrupt_7(){ interruptDispatcher.notifyInterrupt(7); }
void notifyInterrupt_8(){ interruptDispatcher.notifyInterrupt(8); }
void notifyInterrupt_9(){ interruptDispatcher.notifyInterrupt(9); }
void notifyInterrupt_10(){ interruptDispatcher.notifyInterrupt(10); }
void notifyInterrupt_11(){ interruptDispatcher.notifyInterrupt(11); }
void notifyInterrupt_12(){ interruptDispatcher.notifyInterrupt(12); }
void notifyInterrupt_13(){ interruptDispatcher.notifyInterrupt(13); }
void notifyInterrupt_14(){ interruptDispatcher.notifyInterrupt(14); }
void notifyInterrupt_15(){ interruptDispatcher.notifyInterrupt(15); }
void notifyInterrupt_16(){ interruptDispatcher.notifyInterrupt(16); }
void notifyInterrupt_17(){ interruptDispatcher.notifyInterrupt(17); }
void notifyInterrupt_18(){ interruptDispatcher.notifyInterrupt(18); }
void notifyInterrupt_19(){ interruptDispatcher.notifyInterrupt(19); }
void notifyInterrupt_20(){ interruptDispatcher.notifyInterrupt(20); }
void notifyInterrupt_21(){ interruptDispatcher.notifyInterrupt(21); }
void notifyInterrupt_22(){ interruptDispatcher.notifyInterrupt(22); }
void notifyInterrupt_23(){ interruptDispatcher.notifyInterrupt(23); }
void notifyInterrupt_24(){ interruptDispatcher.notifyInterrupt(24); }
void notifyInterrupt_25(){ interruptDispatcher.notifyInterrupt(25); }
void notifyInterrupt_26(){ interruptDispatcher.notifyInterrupt(26); }
void notifyInterrupt_27(){ interruptDispatcher.notifyInterrupt(27); }
void notifyInterrupt_28(){ interruptDispatcher.notifyInterrupt(28); }
void notifyInterrupt_29(){ interruptDispatcher.notifyInterrupt(29); }
void notifyInterrupt_30(){ interruptDispatcher.notifyInterrupt(30); }
void notifyInterrupt_31(){ interruptDispatcher.notifyInterrupt(31); }
void notifyInterrupt_32(){ interruptDispatcher.notifyInterrupt(32); }
void notifyInterrupt_33(){ interruptDispatcher.notifyInterrupt(33); }

InterruptDispatcher::InterruptDispatcher(){
  notifyFunctions[0] = notifyInterrupt_0;
  notifyFunctions[1] = notifyInterrupt_1;
  notifyFunctions[2] = notifyInterrupt_2;
  notifyFunctions[3] = notifyInterrupt_3;
  notifyFunctions[4] = notifyInterrupt_4;
  notifyFunctions[5] = notifyInterrupt_5;
  notifyFunctions[6] = notifyInterrupt_6;
  notifyFunctions[7] = notifyInterrupt_7;
  notifyFunctions[8] = notifyInterrupt_8;
  notifyFunctions[9] = notifyInterrupt_9;
  notifyFunctions[10] = notifyInterrupt_10;
  notifyFunctions[11] = notifyInterrupt_11;
  notifyFunctions[12] = notifyInterrupt_12;
  notifyFunctions[13] = notifyInterrupt_13;
  notifyFunctions[14] = notifyInterrupt_14;
  notifyFunctions[15] = notifyInterrupt_15;
  notifyFunctions[16] = notifyInterrupt_16;
  notifyFunctions[17] = notifyInterrupt_17;
  notifyFunctions[18] = notifyInterrupt_18;
  notifyFunctions[19] = notifyInterrupt_19;
  notifyFunctions[20] = notifyInterrupt_20;
  notifyFunctions[21] = notifyInterrupt_21;
  notifyFunctions[22] = notifyInterrupt_22;
  notifyFunctions[23] = notifyInterrupt_23;
  notifyFunctions[24] = notifyInterrupt_24;
  notifyFunctions[25] = notifyInterrupt_25;
  notifyFunctions[26] = notifyInterrupt_26;
  notifyFunctions[27] = notifyInterrupt_27;
  notifyFunctions[28] = notifyInterrupt_28;
  notifyFunctions[29] = notifyInterrupt_29;
  notifyFunctions[30] = notifyInterrupt_30;
  notifyFunctions[31] = notifyInterrupt_31;
  notifyFunctions[32] = notifyInterrupt_32;
  notifyFunctions[33] = notifyInterrupt_33;  
}
    
void InterruptDispatcher::bind(int pin, EventSource* src){
  sourceRegisteredOnPin[pin] = src; 
  if(pin == ROT_ENC_PIN_SW){
    attachInterrupt(pin, notifyFunctions[pin], RISING);
  } else {
    touchAttachInterrupt(pin, notifyFunctions[pin], TOUCH_THRESHOLD); 
  }
}

void InterruptDispatcher::notifyInterrupt(int pin){
  //Serial.println("");  /* bug/race fix */
  sourceRegisteredOnPin[pin]->notifyInterrupt(pin);
}

/* ------------------------ Event  ------------------------ */

Event::Event(int type){
  this->type = type;
} 
  
int Event::getType(){
  return type;  
}

/* --------------------- EventSource ------------------- */
  
void EventSource::bindInterrupt(int pin){
  interruptDispatcher.bind(pin, this);
}

void EventSource::generateEvent(Event* ev) {
  if (observer != NULL){
    observer->notifyEvent(ev);  
  }
}

void EventSource:: registerObserver(Observer* observer){
  this->observer = observer;
}

/* ------------------------ EventQueue ------------------------ */

EventQueue::EventQueue(){}

Event* EventQueue::rcvedEvent = (Event*)malloc(sizeof(Event));

QueueHandle_t EventQueue::xQueue = xQueueCreate( MAX_EVQUEUE_SIZE, sizeof( Event*)); 

void EventQueue::enqueue(Event* ev){
  if(xQueueSendToBackFromISR( xQueue, (void *)&ev, (BaseType_t *)10) == pdTRUE){      /*Post an item to the back of a queue.
                                                                                        It is safe to use this function from within an interrupt service routine.*/
    //Serial.print( "Enqueue Successful, Queue Counter: " );
    //Serial.println(uxQueueMessagesWaiting(xQueue));
}else{
    //Serial.println( "Enqueue Failed");
  } 
}

Event* EventQueue::dequeue() {
  if(xQueueReceive(xQueue, (void *)&rcvedEvent, 0) == pdTRUE){    
    return rcvedEvent;
  }else{
    return NULL;
  } 
}

/* ------------------------ AsyncFSM   ------------------------ */

AsyncFSM::AsyncFSM(){}
bool AsyncFSM::eventConsumed = true;  
portMUX_TYPE AsyncFSM::eventMux = portMUX_INITIALIZER_UNLOCKED; 
Event* AsyncFSM::ev = NULL;   

void AsyncFSM::notifyEvent(Event* ev){
  eventQueue.enqueue(ev);
}

void AsyncFSM::checkEvents(){  
  if(eventConsumed){                // The previous event has been consumed, extract a new one from the queue
    ev = eventQueue.dequeue();
    portENTER_CRITICAL(&eventMux);
    eventConsumed = false;  
    portEXIT_CRITICAL(&eventMux);
  }else{                           // Get the already extracted event
    ev = eventQueue.rcvedEvent;
  }
  if(ev != NULL){                  // If the event was successfully received from the queue handle it, otherwise ignore and consider the event consumed
    handleEvent(ev);
  }else{
    portENTER_CRITICAL(&eventMux);
    eventConsumed = true; 
    portEXIT_CRITICAL(&eventMux);
  }
}    
