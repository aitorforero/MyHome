#ifndef ROOMCONTROLSTATEMACHINE_H
#define ROOMCONTROLSTATEMACHINE_H

#include <StateMachine.h>
#include <DebugUtils.h>

#include "RoomControlState.h"

class RoomControl;

class RoomControlStateMachine : public StateMachine<RoomControl>
{
    public:
        RoomControlStateMachine(RoomControl* owner) : StateMachine<RoomControl>(owner) {} ;

    
};

#endif