#ifndef _WallSwitch_h
#define _WallSwitch_h

#include <Adafruit_TFTLCD.h>
#include <StateMachine.h>
#include <RotaryEncoder.h>

#define A_PIN 5
#define B_PIN 6
#define SW_PIN 7

class WallSwitch
{
    private:
      Adafruit_TFTLCD* mTFT;
      StateMachine<WallSwitch>* mStateMachine;
      RotaryEncoder* mButton;
      WallSwitch();

    public:
      static WallSwitch* Instance();
      void update();
      StateMachine<WallSwitch>*  getStateMachine() const {return mStateMachine;}
      void setTFT(Adafruit_TFTLCD* newTFT)  {mTFT = newTFT;}
      Adafruit_TFTLCD*  getTFT() const {return mTFT;}
      void setButton(RotaryEncoder* newButton)  {mButton = newButton;}
      RotaryEncoder* getButton() const {return mButton;}
};

#endif
