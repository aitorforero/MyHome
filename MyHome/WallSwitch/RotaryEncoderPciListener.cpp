// 
// 
// 

#include "RotaryEncoderPciListener.h"

RotaryEncoderPciListener::RotaryEncoderPciListener(byte pin, OnPinChange onPinChangeCallback, bool pullUp)
{
	this->pciPin = pin;
	this->onPinChangeCallback = onPinChangeCallback;

	if (pullUp) {
		pinMode(pin, INPUT_PULLUP);
	}
	else {
		pinMode(pin, INPUT);
	}
	this->lastVal = digitalRead(this->pciPin);
}

void RotaryEncoderPciListener::pciHandleInterrupt(byte vector)
{
	byte val = digitalRead(this->pciPin);
	if (val != this->lastVal) {
		this->lastVal = val;
		this->*RotaryEncoderPciListener::onPinChangeCallback(val);
	}
}
