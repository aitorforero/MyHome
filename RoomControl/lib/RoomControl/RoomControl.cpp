#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <DebugUtils.h>
#include "RoomControl.h"


#define INVALID_VALUE -99

RoomControl* RoomControl::_instance = 0;


RoomControl* RoomControl::Instance(){
	if(!RoomControl::_instance) {
		RoomControl::_instance = new RoomControl();
	}
	
	return RoomControl::_instance;
}

void RoomControl::setup() {

	DEBUG_PRINT("Inicializando RoomControl");

}
 
void RoomControl::loop() {
    DEBUG_PRINT("loop start");
	
	mStateMachine->update();
	
    DEBUG_PRINT("loop end");
}



