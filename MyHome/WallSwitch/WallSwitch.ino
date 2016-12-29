#include <PciManager.h>
#include <PciListenerImp.h>


#define A_PIN 4
#define B_PIN 5
#define SW_PIN 6
#define LED_PIN 11
#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255
#define STEP_BRIGHTNESS 5

void onA(byte);
void onB(byte);
void onSW(byte);
void onCounterClockWise();
void onClockWise();
void setBrightness(byte);

PciListenerImp listenerA(A_PIN, onA, true);
PciListenerImp listenerB(B_PIN, onB, true);
PciListenerImp listenerSW(SW_PIN, onSW, true);

byte AValue;
byte BValue;
byte prevValue;

byte brightness;




void setup() {
	Serial.begin(9800);
	Serial.println("Initializing...");

	pinMode(LED_PIN, OUTPUT);
	setBrightness(125);

	PciManager.registerListener(A_PIN, &listenerA);
	PciManager.registerListener(B_PIN, &listenerB);
	PciManager.registerListener(SW_PIN, &listenerSW);

	// Initialize Rotary Encoder
	AValue = digitalRead(A_PIN);
	BValue = digitalRead(B_PIN);
	prevValue = AValue * 2 + BValue;
	onChange();


	Serial.println("Ready.");
}

void loop() {
}

void setBrightness(byte value) {
	brightness = value;
	Serial.println(value);
	analogWrite(LED_PIN, brightness);
}

void onChange() {
	byte value = AValue * 2 + BValue;
	static int8_t enc_states[] = { 0,  1, -1,  0,
		-1,  0,  0,  1,
		1,  0,  0, -1,
		0, -1,  1,  0 };

	int8_t direction = enc_states[4 * value + prevValue];
	prevValue = value;
	if (direction > 0) {
		onClockWise();
	}
	else if (direction < 0) {
		onCounterClockWise();
	}
}

void onA(byte changeKind) {
	AValue = changeKind;
	onChange();
}

void onB(byte changeKind) {
	BValue = changeKind;
	onChange();
}

void onSW(byte changeKind) {
	if (!changeKind) {
		Serial.println("Pulsado");
	}
	else {
		Serial.println("Suelto");
	}
}

void onClockWise() {
	byte newBrightness = ((brightness + STEP_BRIGHTNESS) > MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : (brightness + STEP_BRIGHTNESS);
	setBrightness(newBrightness);
}

void onCounterClockWise() {
	byte newBrightness = ((brightness - STEP_BRIGHTNESS) < MIN_BRIGHTNESS) ? MIN_BRIGHTNESS : (brightness - STEP_BRIGHTNESS);
	setBrightness(newBrightness);
}
