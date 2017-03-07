#define DEBUG

#define byte uint8_t


#include <Arduino.h>
#include <avr/wdt.h>

// This libraries are here to avoid PlatformIO compiling error
// due not file found
#include <FastDelegate.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Configuration.h>
#include <Event.h>
#include <EventArgs.h>
#include <Menu.h>


#include <Debug.h>
#include <HomeAutomation.h>
#include <RotaryEncoder.h>

#include <InitializingState.h>






/*
byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x91, 0x62 };
char server[] = "192.168.0.14";
int port = 8080;
IPAddress ip(192, 168, 0, 177);
*/


HomeAutomation* homeAutomation;
RotaryEncoder* rotaryEncoder;
unsigned long time;


void setup()
{
  Debug::initialize(9600);
  wdt_disable();
  //Initialize serial communications for debugin

  Debug::debug("System starting...");
    
  /* Enable watchdog.
     If the loop last more than 8s restart the hardware */
  wdt_enable(WDTO_8S);
}

void loop()
{
    WallSwitch::Instance()->update();
    time = millis();
    Debug::debug(30,"Time: %",time);

    wdt_reset();
}

/*



void onCounterClockWise()
{
    Serial.println("onCCW");
    homeAutomation->raiseCommand("Light_GF_Corridor_Ceiling","ON");
}
*/