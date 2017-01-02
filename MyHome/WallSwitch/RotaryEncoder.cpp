// 
// 
// 

#include <Arduino.h>



#include "PciManager.h"
#include "RotaryEncoder.h"
#include "RotaryEncoderPciListener.h"

RotaryEncoder::RotaryEncoder(byte pinA, byte pinB, byte pinSW)
{
	this->_pinA = pinA;
	this->_pinB = pinB;
	this->_pinSW = pinSW;


	this->initialize();
}

void RotaryEncoder::initialize() {
	RotaryEncoderPciListener listenerA(this->_pinA, &RotaryEncoder::onA, true);
	RotaryEncoderPciListener listenerB(this->_pinB, &RotaryEncoder::onB, true);
	RotaryEncoderPciListener listenerSW(this->_pinSW, &RotaryEncoder::onSW, true);

	PciManager.registerListener(this->_pinA, &listenerA);
	PciManager.registerListener(this->_pinB, &listenerB);
	PciManager.registerListener(this->_pinSW, &listenerSW);
}


void RotaryEncoder::onA(byte changeKind) {
	_AValue = changeKind;
	onChange();
}

void RotaryEncoder::onB(byte changeKind) {
	_BValue = changeKind;
	onChange();
}

void RotaryEncoder::onSW(byte changeKind) {
	if (!changeKind) {
		Serial.println("Pulsado");
	}
	else {
		Serial.println("Suelto");
	}
}


void RotaryEncoder::onChange() {
	byte value = _AValue * 2 + _BValue;
	static int8_t enc_states[] = { 0,  1, -1,  0,
								  -1,  0,  0,  1,
		                           1,  0,  0, -1,
		                           0, -1,  1,  0 };

	int8_t direction = enc_states[4 * value + _prevValue];
	_prevValue = value;
	if (direction > 0) {
		this->onClockWise();
	}
	else if (direction < 0) {
		this->onCounterClockWise();
	}
}

void RotaryEncoder::handleClockWise(OnEventCallback onClockWise) {
	this->onClockWise = onClockWise;
}

void RotaryEncoder::handleCounterClockWise(OnEventCallback onCounterClockWise) {
	this->onCounterClockWise = onCounterClockWise;
}

void RotaryEncoder::handleClick(OnEventCallback onClick) {
	this->onClick = onClick;
}