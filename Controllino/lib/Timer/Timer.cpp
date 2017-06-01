#include "Timer.h"
#include <Arduino.h>
#include <Event.h>
#include <EventArgs.h>

Timer* Timer::timers = NULL;

Timer* Timer::Create(unsigned long period) {
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
    while(currentTimer->nextTimer != NULL) {
        if(currentTimer->isEnabled && (currentTimer->elapsedTime + now)>=currentTimer->_period) {
            currentTimer->onTick();
        }
        currentTimer = currentTimer->nextTimer;
    }
}

Event<EventArgs>* Timer::tick(){
	return this->_tick;
}


void Timer::enable(){
    this->elapsedTime = 0;
    this->isEnabled = true;
}


void Timer::disable(){
    this->elapsedTime = 0;
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
    isEnabled = false;
    _period = period;
    _tick = new Event<EventArgs>;
    elapsedTime = 0;
}

void Timer::onTick(){
	elapsedTime = 0;
    EventArgs e = new EventArgs(this);
	this->_tick->raise(&e);
}

/*
#ifndef Timer_h
#define Timer_h

#include <Arduino.h>
#include <Event.h>
#include <EventArgs.h>

class Timer {
    public:
        static Timer* Create(unsigned long period);
        static void loop();
        Event<EventArgs>* tick();
        void enable();
        void disable();
        void destroy();

    
    private:
        Timer(unsigned long period);
        bool isEnabled;
        unsigned long _period;
        unsigned long elapsedTime;
        void onTick();
        Event<EventArgs>* _tick;
        Timer* nextTimer;
        Timer* previousTimer;
        static Timer* timers;
};

#endif
 
 */