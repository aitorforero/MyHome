#include "Arduino.h"
#include "RotaryEncoderPciListener.h"
#include "RotaryEncoder.h"


#define A_PIN 4
#define B_PIN 5
#define SW_PIN 6
#define LED_PIN 11
#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255
#define STEP_BRIGHTNESS 5


RotaryEncoder rotaryEncoder(A_PIN, B_PIN, SW_PIN);


void onCounterClockWise();
void onClockWise();
void setBrightness(byte);


byte AValue;
byte BValue;
byte prevValue;

byte brightness;




void setup() {
	Serial.begin(9800);
	Serial.println("Initializing...");

	pinMode(LED_PIN, OUTPUT);
	setBrightness(125);


	Serial.println("Ready.");
}

void loop() {
}

void setBrightness(byte value) {
	brightness = value;
	Serial.println(value);
	analogWrite(LED_PIN, brightness);
}





void onClockWise() {
	byte newBrightness = ((brightness + STEP_BRIGHTNESS) > MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : (brightness + STEP_BRIGHTNESS);
	setBrightness(newBrightness);
}

void onCounterClockWise() {
	byte newBrightness = ((brightness - STEP_BRIGHTNESS) < MIN_BRIGHTNESS) ? MIN_BRIGHTNESS : (brightness - STEP_BRIGHTNESS);
	setBrightness(newBrightness);
}
