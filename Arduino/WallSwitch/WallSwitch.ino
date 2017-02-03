#define byte uint8_t


#include <Arduino.h>
#include <avr/wdt.h>

// This libraries are here to avoid PlatformIO compiling error
// due not file found
#include <SPI.h>
#include <EEPROM.h>

#include <HomeAutomation.h>
#include <RotaryEncoder.h>
#include <Configuration.h>
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
    wdt_disable();

    Serial.begin(9600);
    Serial.println("Initializing...");
    
/*
    Configuration::load();
    homeAutomation = new HomeAutomation(
      Configuration::getMACAddress(), 
      Configuration::getServer().IPAddress, 
      Configuration::getServer().port, 
      IPAddress(
        Configuration::getIPAddress()[0],
        Configuration::getIPAddress()[1],
        Configuration::getIPAddress()[2],
        Configuration::getIPAddress()[3]));
        
    rotaryEncoder = new RotaryEncoder(A_PIN, B_PIN, SW_PIN);*/
    Serial.println("Ready.");

    wdt_enable(WDTO_250MS);
}

void loop()
{   
    WallSwitch::Instance()->update();
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
