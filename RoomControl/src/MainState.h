#ifndef _MainState_h
#define _MainState_h

#include "RoomControlState.h"
#include "RoomControl.h"
class MainState : public RoomControlState
{
    public:
        MainState(RoomControl* rc):RoomControlState(rc){};
 
};


#endif
