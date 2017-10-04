#ifndef _ConfigurationMenuState_h
#define _ConfigurationMenuState_h


#include "Controls/ControlContainer.h"
#include "Controls/Label.h"
#include "RoomControl.h"
#include "ButtonEventHandlerState.h"

#define MENU_OPTION_COUNT 5

class ConfigurationMenuState : public ButtonEventHandlerState<RoomControl>, private ControlContainer
{ 
    private:
      Label titleLabel;  
      Label optionNameLabel;  
      Label optionValueLabel;  
      
      const char *menuOptions[MENU_OPTION_COUNT];
      int selectedOption;
      
      ConfigurationMenuState();
      
      void changeSelectedOption(RoomControl* rc,int value);
      void drawMenu(RoomControl* rc);
      void onTwoButtonsClick(RoomControl* rc);
      


    public:
      static ConfigurationMenuState* Instance();
      void enter(RoomControl* rc);
      void onLeftButtonClick(RoomControl* rc);
      void onRightButtonClick(RoomControl* rc);
};


#endif