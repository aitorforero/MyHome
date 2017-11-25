#ifndef _InitializingState_h
#define _InitializingState_h

#include "RoomControlState.h"
#include "RoomControl.h"
class InitializingState : public RoomControlState
{
    private:
      void initializeScreen();
      void initializeEthernet();
      void initializeButtons();
      
    public:
      InitializingState(RoomControl* rc):RoomControlState(rc){};
      void execute();
      const char * getName();

};


#endif