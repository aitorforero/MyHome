
#include <Arduino.h>
#include <EEPROM.h>
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




/*
#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

 
void draw() 
{
  
  u8g.setFont(u8g_font_profont15);
  u8g.drawStr(3, 15, "Bienvenido");
  u8g.setFont(u8g_font_profont12);
  u8g.drawStr(2, 37, "Encender"); 
  u8g.drawStr(2, 57, "Apagar");
 u8g.drawStr(2, 77, "Apagar");
 u8g.drawStr(2, 97, "Apagar");
}
 
void setup(void) 
{
  Serial.begin(9600);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // Blanco
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensidad
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}
 
void loop(void) 
{
  u8g.firstPage();  
  do
  {
    draw();
  } while( u8g.nextPage() );
   
  delay(50);
}
*/