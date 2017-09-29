#ifndef _ConfigurationMenuState_h
#define _ConfigurationMenuState_h


#include "Controls/ControlContainer.h"
#include "Controls/Label.h"
#include "RoomControl.h"
#include "ButtonEventHandlerState.h"

#define MENU_OPTION_COUNT 5

class ConfigurationMenuState : public ButtonEventHandlerState<RoomControl>, public ControlContainer
{ 
    private:
      Label Title;  
      ConfigurationMenuState();
      const char *menuOptions[MENU_OPTION_COUNT];
      int selectedOption;
      void drawMenu(RoomControl* rc);
      void onTwoButtonsClick(RoomControl* rc);
      


    public:
      static ConfigurationMenuState* Instance();
      void enter(RoomControl* rc);
      void onLeftButtonClick(RoomControl* rc);
      void onRightButtonClick(RoomControl* rc);
};


#endif