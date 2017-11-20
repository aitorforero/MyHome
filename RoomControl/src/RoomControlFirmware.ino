
#include <Arduino.h>
#include <EEPROM.h>

#define TRACE_LEVEL_DEBUG 
#include <DebugUtils.h>

#include "RoomControl.h"

#include "Configuration.h"


void setup()
{
  Serial.begin(115200);
 // wdt_disable();
  //Initialize serial communications for debugin
 DEBUG_PRINT("System starting...");

  /* Enable watchdog.
     If the loop last more than 8s restart the hardware */
//  wdt_enable(WDTO_8S);
}

void loop()
{
    RoomControl::Instance()->loop();
    
    //    wdt_reset();
}
