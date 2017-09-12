#ifndef _MainState_h
#define _MainState_h

#include "ButtonEventHandlerState.h"
#include "RoomControl.h"
class MainState : public ButtonEventHandlerState<RoomControl>
{
    private:
      MainState(){};

    public:
      static MainState* Instance();
};


#endif
