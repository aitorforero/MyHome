// RotaryEncoder.h

#ifndef _ROTARYENCODER_h
#define _ROTARYENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



typedef void(*OnEventCallback)();

class RotaryEncoder
{
 private:
	 void initialize();
	 void onA(byte);
	 void onB(byte);
	 void onSW(byte);
	 void onChange();
	 byte _pinA;
	 byte _pinB;
	 byte _pinSW;
	 byte _AValue;
	 byte _BValue;
	 byte _prevValue;
	 OnEventCallback onClockWise;
	 OnEventCallback onCounterClockWise;
	 OnEventCallback onClick;


 public:
	RotaryEncoder(byte, byte, byte);
	void handleClockWise(OnEventCallback onClockWise);
	void handleCounterClockWise(OnEventCallback onCounterClockWise);
	void handleClick(OnEventCallback onClick);


};


#endif

