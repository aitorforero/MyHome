#include "Timer.h"
#include <Arduino.h>
#include <Event.h>
#include <EventArgs.h>

Timer* Timer::timers = NULL;

Timer* Timer::create(unsigned long period) {
	Serial.print("Creating timer for ");
	Serial.print(period);
	Serial.println("ms...");
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
    }
    
    
    return newTimer;
}

void Timer::loop(){
	unsigned long now = millis();
    
	
    Timer* currentTimer = Timer::timers;
    while(currentTimer) {
        if(currentTimer->isEnabled && (now - currentTimer->startTime)>=currentTimer->_period) {
			currentTimer->onTick();
		}
        currentTimer = currentTimer->nextTimer;
    }
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
    bool destroy = false;
    
    if (Timer::timers == this) {
        Timer::timers = this->nextTimer;
	} else {
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
	unsigned long i = 0;
	startTime = millis();
    EventArgs e(this);
	this->_tick->raise(&e);
}

