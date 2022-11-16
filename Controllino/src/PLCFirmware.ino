#include <Arduino.h>
#include <EEPROM.h>
#include <DebugUtils.h>
#include "PLC.h"
#include "Configuration.h"



 
void setup()
{
    Serial.begin(115200);
    PLC::setup();
}
 
void loop()
{
    DEBUG_PRINT("loop");
    PLC::loop();
}