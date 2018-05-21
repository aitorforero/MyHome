#ifndef _RoomControlEventsController_h
#define _RoomControlEventsController_h

#include "MQTTEvents.h"
#include "ButtonEvents.h"

class RoomControlEventsController : public ButtonEventsController, public MQTTEventsController
{
       public:
        RoomControlEventsController(RoomControl* owner):ButtonEventsController(owner), MQTTEventsController(owner){} ;
};
#endif