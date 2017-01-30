#ifndef _RotaryEncoder_h
#define _RotaryEncoder_h
 
#include "Arduino.h"

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

    PciListenerImp2* listenerA;
    PciListenerImp2* listenerB;
    PciListenerImp2* listenerSW;

    typedef void(*EventCallback)();

    EventCallback onClick;
    EventCallback onClockWise;
    EventCallback onCounterClockWise;

  public:
    RotaryEncoder(byte pinA, byte pinB, byte pinSW);
    void setOnClick(EventCallback eventCallback);
    void setOnClockWise(EventCallback eventCallback);
    void setOnCounterClockWise(EventCallback eventCallback);

    void pciHandleChange(byte changedTo, PciListenerImp2* listener);
};

#endif
