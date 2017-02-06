#ifndef _WallSwitch_h
#define _WallSwitch_h

#include <Adafruit_TFTLCD.h>
#include <StateMachine.h>


class WallSwitch
{
    private:
      Adafruit_TFTLCD* mTFT;
      StateMachine<WallSwitch>* mStateMachine;
      WallSwitch();

    public:
      static WallSwitch* Instance();
      void update();
      StateMachine<WallSwitch>*  getStateMachine() const {return mStateMachine;}
      void setTFT(Adafruit_TFTLCD* newTFT)  {mTFT = newTFT;}
      Adafruit_TFTLCD*  getTFT() const {return mTFT;}
};

#endif
