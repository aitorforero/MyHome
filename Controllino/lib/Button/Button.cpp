
#include <Event.h>
#include "Button.h"
#include <EventArgs.h>
#include <FastDelegate.h>
//#define DEBUG
#include <DebugUtils.h>


Button::Button(){};

Button::Button(byte pin, byte pushedValue, bool usePullUp,  Event<EventArgs>::Handler h, unsigned long debounceTime = 50){
    this->_pin = pin;
    this->_pushedValue = pushedValue;
	this->_click = new Event<EventArgs>;
	this->_click->addHandler(h);
    
	DEBUG_PRINT("pin: ");
    DEBUG_PRINT(this->_pin);
	DEBUG_PRINT("pushedValue: ");
    DEBUG_PRINT(this->_pushedValue);

    
    byte mode =  usePullUp ? INPUT_PULLUP : INPUT;
    
    pinMode(pin, mode);
    
    unsigned long period = debounceTime >> 3;
    t = Timer::create(period);
    t->tick()->addHandler(MakeDelegate(this, &Button::onTick));
    t->enable();
}

Event<EventArgs>* Button::click(){
	return this->_click;
}
 
void Button::onTick(EventArgs* e){
	DEBUG_PRINT("				Button::onTick start");
	
    byte readValue = digitalRead(_pin);
	byte value = !(readValue ^ this->_pushedValue);
	DEBUG_PRINT("pin: ");
    DEBUG_PRINT(_pin);
	DEBUG_PRINT("pushedValue: ");
    DEBUG_PRINT(this->_pushedValue);
    DEBUG_PRINT("readValue: ");
    DEBUG_PRINT(readValue);
    DEBUG_PRINT("Value: ");
    DEBUG_PRINT(value);
    DEBUG_PRINT("devounceValue: ");
    DEBUG_PRINT(this->devounceValue);
    if(this->devounceValue==0xFF && value==0) {
        this->devounceValue = 0;
        EventArgs eClick(this);
        this->_click->raise(&eClick); 
	} else {
		this->devounceValue = (this->devounceValue << 1) | value; 
    } 
	DEBUG_PRINT("				Button::onTick end");
}

byte Button::pin(){
    return this->_pin;
}