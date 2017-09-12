#ifndef _InitializingState_h
#define _InitializingState_h

#include "ButtonEventHandlerState.h"
#include "RoomControl.h"
class InitializingState : public ButtonEventHandlerState<RoomControl>
{
    private:
      InitializingState(){};
      void initializeScreen(RoomControl* rc);
      void initializeEthernet(RoomControl* rc);
      void initializeButtons(RoomControl* rc);
      
    public:
      static InitializingState* Instance();
      void execute(RoomControl* rc);
};


#endif