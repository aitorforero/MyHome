#ifndef _ConfigurationEditNameState_h
#define _ConfigurationEditNameState_h


#include "RoomControl.h"
#include "ButtonEventHandlerState.h"

#define MIN_NUMBER 48 
#define MAX_NUMBER 57 
#define MIN_UPPER_CASE 65 
#define MAX_UPPER_CASE 90
#define MIN_LOWER_CASE 97 
#define MAX_LOWER_CASE 122
#define NAME_LENGTH 8

class ConfigurationEditNameState : public ButtonEventHandlerState<RoomControl>
{ 
    private:
      ConfigurationEditNameState();
      void draw(RoomControl* rc);
    
      int pos;

    public:
      static ConfigurationEditNameState* Instance();
      void enter(RoomControl* rc);
};


#endif