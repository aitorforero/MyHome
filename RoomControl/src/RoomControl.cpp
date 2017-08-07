#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#define DEBUG
#include <DebugUtils.h>
#include <Button.h>
#include <EventArgs.h>
#include <Timer.h>
#include "InitializingState.h"
#include "RoomControl.h"
#include "ButtonEventHandler.h"


#define INVALID_VALUE -99

RoomControl::RoomControl(){
	line = 0;
	mStateMachine = new StateMachine<RoomControl>(this);
	mStateMachine->changeState(InitializingState::Instance());
};

RoomControl* RoomControl::Instance(){
	static RoomControl instance;

	return &instance;
};


 
void RoomControl::loop() {
    DEBUG_PRINT("loop start");
    Timer::loop();
	mStateMachine->update();
	
    DEBUG_PRINT("loop end");
}


void RoomControl::changeState(State<RoomControl>* s){
	mStateMachine->changeState(s);	
}


void RoomControl::println(const char* text){
	int i;
	u8g->setFont(u8g_font_profont10);

	if (line==5) {
		for(i=0;i<4;i++){
			memcpy(buffer[i],buffer[i+1],81);
		}
		memcpy(buffer[4],text,81);
	} else {
		memcpy(buffer[line],text,81);
	}
	
	
	u8g->firstPage();  
	do
	{
		for(i=0;i<=line;i++){
			u8g->drawStr(2, (i+1)*12, buffer[i]);
		}
	} while(u8g->nextPage() );

	if (line<5) {
		line++;
	}	
}

void RoomControl::onLeftButtonClick(EventArgs* e){
	INFO_PRINT("Left Click!!!");
	((ButtonEventHandler*)mStateMachine)->onLeftButtonClick(this);	
    
}

void RoomControl::onRightButtonClick(EventArgs* e){
	INFO_PRINT("Right Click!!!");
	INFO_PRINT(((Button*)e->sender)->pin());
}
