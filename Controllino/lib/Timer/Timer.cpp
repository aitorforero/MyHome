#include "Timer.h"
#include <Arduino.h>
#include <Event.h>
#include <EventArgs.h>
#include <DebugUtils.h>

Timer* Timer::timers = NULL;

Timer* Timer::create(unsigned long period) {
	DEBUG_PRINT("Creating timer for ");
	DEBUG_PRINT(period);
	DEBUG_PRINT("ms...");
    Timer* newTimer = new Timer(period);
    
    newTimer->_period = period;
    
    if (Timer::timers == NULL) {
        Timer::timers = newTimer;
	} else {
        Timer* currentTimer = Timer::timers;
        while(currentTimer->nextTimer != NULL) {
            currentTimer = currentTimer->nextTimer;
        }
        
        currentTimer->nextTimer = newTimer;
		newTimer->previousTimer = currentTimer;
    }
    
    
    return newTimer;
}

void Timer::loop(){
	DEBUG_PRINT("	Timer::loop start");
	unsigned long now = millis();

	int i = 0;
    Timer* currentTimer = Timer::timers;
    while(currentTimer) {
		i++;
		DEBUG_PRINT("		Timer::loop Timer ");
		DEBUG_PRINT(i);
		DEBUG_PRINT("			isEnabled ");
		DEBUG_PRINT(currentTimer->isEnabled);
		DEBUG_PRINT("			period ");
		DEBUG_PRINT(currentTimer->_period);
		DEBUG_PRINT("			startTime ");
		DEBUG_PRINT(currentTimer->startTime);
		DEBUG_PRINT("			now ");
		DEBUG_PRINT(now);
        if(currentTimer->isEnabled && (now - currentTimer->startTime)>=currentTimer->_period) {
			currentTimer->onTick();
		}
        currentTimer = currentTimer->nextTimer;
    }
	DEBUG_PRINT("	Timer::loop end");
}

Event<EventArgs>* Timer::tick(){
	return this->_tick;
}

 
void Timer::enable(){
    this->startTime = millis();
    this->isEnabled = true;
}


void Timer::disable(){
    this->isEnabled = false;
}

void Timer::destroy(){

    if (Timer::timers == this) {
        Timer::timers = this->nextTimer;
	} else {
    	bool destroy = false;
        Timer* currentTimer = Timer::timers;
        while(!destroy && currentTimer->nextTimer != NULL) {
            if(currentTimer == this) {
               this->previousTimer->nextTimer = this->nextTimer;
				destroy = true;
            } else {
                currentTimer = currentTimer->nextTimer;      
            }
        }
    }
    
    delete this;

};


Timer::Timer(unsigned long period) {
    this->isEnabled = false;
    this->_period = period;
    this->_tick = new Event<EventArgs>;
	this->nextTimer=NULL;
}

void Timer::onTick(){ 
	DEBUG_PRINT("			Timer::onTick start");
	unsigned long i = 0;
	startTime = millis();
    EventArgs e(this);
	this->_tick->raise(&e);
	DEBUG_PRINT("			Timer::onTick end");
}
