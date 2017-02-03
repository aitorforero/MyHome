#ifndef _WallSwitch_h
#define _WallSwitch_h

#include <Adafruit_TFTLCD.h>
#include <StateMachine.h>


// Pines de conexion del LCD 
#define LCD_CS A11 // Chip Select - Pin analogico 3
#define LCD_CD A10 // Command/Data - Pin Analogico 2
#define LCD_WR A9 // LCD Write - Pin Analogico 1
#define LCD_RD A8 // LCD Read - Pin Analogico 0
#define LCD_RESET A12 // LCD Reset - Pin Analogico 4




class WallSwitch
{
    private:
      Adafruit_TFTLCD* mTFT;
      StateMachine<WallSwitch>* mStateMachine;
      WallSwitch();  
  
    public:
      static WallSwitch* Instance();
      void update();
};

#endif
