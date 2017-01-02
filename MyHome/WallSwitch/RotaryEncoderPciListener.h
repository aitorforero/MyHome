// RotaryEncoderPciListener.h

#ifndef _ROTARYENCODERPCILISTENER_h
#define _ROTARYENCODERPCILISTENER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PciListener.h"
#include "RotaryEncoder.h"

typedef  void (RotaryEncoder::*OnPinChange)(byte);

class RotaryEncoderPciListener : public PciListener
{
public:
	RotaryEncoderPciListener(byte pin, OnPinChange onPinChangeCallback, bool pullUp = false);
	virtual void pciHandleInterrupt(byte vector);
	byte lastVal;
private:
	OnPinChange onPinChangeCallback;
};


#endif

