#define byte uint8_t


#include <Arduino.h>
#include <avr/wdt.h>

// This libraries are here to avoid PlatformIO compiling error
// due not file found
#include <SPI.h>
#include <EEPROM.h>
#include <Configuration.h>

#include <Debug.h>
#include <HomeAutomation.h>
#include <RotaryEncoder.h>

#include <InitializingState.h>




#define A_PIN 5
#define B_PIN 6
#define SW_PIN 7

/*
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x91, 0x62 };
char server[] = "192.168.0.14";
int port = 8080;
IPAddress ip(192, 168, 0, 177);
*/

void onCounterClockWise();
void onClockWise();
void onClick();

HomeAutomation* homeAutomation;
RotaryEncoder* rotaryEncoder;


void setup()
{
  Debug.initialize(9600);
  wdt_disable();
  //Initialize serial communications for debugin

  Debug::debug("Initializing...");
  /* Enable watchdog.
     If the loop last more than 8s restart the hardware */
  wdt_enable(WDTO_8S);
}

void loop()
{
    Debug::debug("Loop;");
    WallSwitch* ws = WallSwitch::Instance();
    Debug::debug("updating");
    //delay(5000);
    //ws->update();
    wdt_reset();
}


void onClockWise()
{
    Serial.println("onCW");
}


void onCounterClockWise()
{
    Serial.println("onCCW");
    homeAutomation->raiseCommand("Light_GF_Corridor_Ceiling","ON");
}
