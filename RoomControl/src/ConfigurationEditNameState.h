#ifndef _ConfigurationEditNameState_h
#define _ConfigurationEditNameState_h


#include "RoomControl.h"
#include "ButtonEventHandlerState.h"


class ConfigurationEditNameState : public ButtonEventHandlerState<RoomControl>
{ 
    private:
      ConfigurationEditNameState();
      void draw(RoomControl* rc);

    public:
      static ConfigurationEditNameState* Instance();
      void enter(RoomControl* rc);
};


#endif