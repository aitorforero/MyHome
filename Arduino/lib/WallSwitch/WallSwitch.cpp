

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h>
#include <StateMachine.h>
#include "InitializingState.h"   
#include "WallSwitch.h"





WallSwitch::WallSwitch()
{
  mTFT = new Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

  mStateMachine = new StateMachine<WallSwitch>(this);
  mStateMachine->changeState(InitializingState::Instance());
};

WallSwitch* WallSwitch::Instance()
{
  static WallSwitch instance;

  return &instance;
};


void WallSwitch::update()
{
  mStateMachine->update();
};