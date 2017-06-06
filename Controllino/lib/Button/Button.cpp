#include "Button.h"
#include <Event.h>
#include <EventArgs.h>
#include <FastDelegate.h>


Button::Button(byte pin, byte pushedValue, bool usePullUp, unsigned long debounceTime = 50){
    this->_pin = pin;
    this->_pushedValue = pushedValue;
    
    
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
	//Serial.println("Button::onTick");
	
    static byte devounceValue = 0;
    byte readValue = !(digitalRead(_pin) ^ this->_pushedValue);
    //Serial.print("readValue: ");
    //Serial.println(readValue);
    //Serial.print("devounceValue: ");
    //Serial.println(devounceValue);
    if(devounceValue==0xFF && readValue==0) {
        devounceValue = 0;
		Serial.println("Button::onTick => click");
        EventArgs e = new EventArgs(this);
        this->_click->raise(&e);
	} else {
		devounceValue = (devounceValue << 1) | readValue; 
    } 
}

byte Button::pin(){
    return this->_pin;
}