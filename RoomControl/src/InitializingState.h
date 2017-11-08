#ifndef _InitializingState_h
#define _InitializingState_h

#include "RoomControlState.h"
#include "RoomControl.h"
class InitializingState : public RoomControlState
{
    private:
      void initializeScreen(RoomControl* rc);
      void initializeEthernet(RoomControl* rc);
      void initializeButtons(RoomControl* rc);
      
    public:
      InitializingState() {};
      RoomControlState* execute(RoomControl* rc);
};


#endif