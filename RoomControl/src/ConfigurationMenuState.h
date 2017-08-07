#ifndef _ConfigurationMenuState_h
#define _ConfigurationMenuState_h

#include <State.h>
#include "RoomControl.h"
#include "ButtonEventHandler.h"

#define MENU_OPTION_COUNT 2

class ConfigurationMenuState : public State<RoomControl>, public ButtonEventHandler
{
    private:
      ConfigurationMenuState();
      const char *menuOptions[MENU_OPTION_COUNT];
      int selectedOption;
      void drawMenu(RoomControl* rc);

    public:
      static ConfigurationMenuState* Instance();
      void enter(RoomControl* rc);
      void execute(RoomControl* rc);
      void exit(RoomControl* rc);
      void onLeftButtonClick(RoomControl* rc);
      void onRightButtonClick(RoomControl* rc);
};


#endif