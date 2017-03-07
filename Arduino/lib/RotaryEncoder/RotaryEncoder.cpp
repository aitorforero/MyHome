#include "RotaryEncoder.h"
#include <Event.h>
#include <EventArgs.h>
#include <PciManager.h>
#include <PciListenerImp2.h>
#include <IPciChangeHandler.h>


void RotaryEncoder::onA(byte changeKind)
{
  AValue = changeKind;
  onChange();
}

void RotaryEncoder::onB(byte changeKind)
{
  BValue = changeKind;
  onChange();
}

void RotaryEncoder::onSW(byte changeKind)
{
    if(!changeKind){
    } else {
        onClick();
    }
}

void RotaryEncoder::onChange()
{
  byte value = AValue * 2 + BValue;
  static int8_t enc_states[] = {0,  1, -1,  0,
                               -1,  0,  0,  1,
                                1,  0,  0, -1,
                                0, -1,  1,  0};

  int8_t direction = enc_states[4 * value + prevValue];
  prevValue = value;
  if(direction > 0) {
      onClockWise();
  } else if(direction < 0) {
      onCounterClockWise();
  }
}

RotaryEncoder::RotaryEncoder(byte pinA, byte pinB, byte pinSW)
{


  listenerA = new PciListenerImp2();
  listenerB = new PciListenerImp2();
  listenerSW = new PciListenerImp2();

  listenerA->init(pinA, this, true);
  listenerB->init(pinB, this, true);
  listenerSW->init(pinSW, this, true);

  PciManager.registerListener(pinA, listenerA);
  PciManager.registerListener(pinB, listenerB);
  PciManager.registerListener(pinSW, listenerSW);
}



Event<EventArgs>* RotaryEncoder::click()
{
	return this->_click;
};


Event<EventArgs>* RotaryEncoder::clockWise()
{
	return this->_clockWise;
};

Event<EventArgs>* RotaryEncoder::counterClockWise() 
{
	return this->_counterClockWise;
};



void RotaryEncoder::pciHandleChange(byte changedTo, PciListenerImp2* listener){
  if (listener == listenerA)
  {
    onA(changedTo);
  }
  else if (listener == listenerB)
  {
    onB(changedTo);
  }
  else
  {
    onSW(changedTo);
  }
}


void RotaryEncoder::onClick()
{
	EventArgs e = new EventArgs(this);
	this->click()->raise(&e);
};

void RotaryEncoder::onClockWise()
{
	EventArgs e = new EventArgs(this);
	this->clockWise()->raise(&e);
};
void RotaryEncoder::onCounterClockWise()
{
	EventArgs e = new EventArgs(this);
	this->counterClockWise()->raise(&e);
};