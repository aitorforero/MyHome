#define CONTROLLINO_MEGA


#include <Arduino.h>
#include <PLC.h>
#include <DebugUtils.h>


 
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