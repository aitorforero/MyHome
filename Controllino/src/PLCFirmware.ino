#define CONTROLLINO_MEGA

#include <Arduino.h>
#include <PLC.h>


 
void setup()
{
  Serial.begin(115200);
  PLC::setup();
}
 
void loop()
{
    PLC::loop();
}