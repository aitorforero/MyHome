#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <pin_magic.h>
#include <Adafruit_TFTLCD.h>
#include <Configuration.h>
#include <StateMachine.h>


#include "InitializingState.h"
#include "WallSwitch.h"







WallSwitch::WallSwitch()
{

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
