#ifndef _RotaryEncoder_h
#define _RotaryEncoder_h
 
#include <Arduino.h>
#include <Event.h>
#include <EventArgs.h>
#include <PciManager.h>
#include <PciListenerImp2.h>
#include <IPciChangeHandler.h>



class RotaryEncoder : public IPciChangeHandler
{
  private:
    byte AValue;
    byte BValue;
    byte prevValue;

    void onA(byte);
    void onB(byte);
    void onSW(byte);
    void onChange();
    
    void onClick();
    void onClockWise();
    void onCounterClockWise();

    PciListenerImp2* listenerA;
    PciListenerImp2* listenerB;
    PciListenerImp2* listenerSW;
    
    Event<EventArgs>* _click;
    Event<EventArgs>* _clockWise;
    Event<EventArgs>* _counterClockWise;


  public:
    RotaryEncoder(byte pinA, byte pinB, byte pinSW);
    Event<EventArgs>* click();
    Event<EventArgs>* clockWise();
    Event<EventArgs>* counterClockWise();
    
    void pciHandleChange(byte changedTo, PciListenerImp2* listener);
};

#endif
