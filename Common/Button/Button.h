#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include <Event.h>
#include <EventArgs.h>
#include <Timer.h>

class Button {
    private:
        byte _pin;
        byte _pushedValue;
        Event<EventArgs>* _click;  
        Timer* t;
        void onTick(EventArgs* e);
        byte devounceValue;
    
    public:
        Button();
        Button(byte pin, byte pushedValue, bool usePullUp, Event<EventArgs>::Handler h, unsigned long debounceTime = 50);
        Event<EventArgs>* click();
        byte pin();
};

#endif