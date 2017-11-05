#ifndef _ConfigurationEditNameState_h
#define _ConfigurationEditNameState_h


#include "RoomControl.h"
#include "RoomControlState.h"
#include "Controls/Label.h"
#include "Controls/Icon.h"
#include "Controls/ButtonBar.h"
#include "Controls/TextBox.h"

#define NAME_LENGTH 8

class ConfigurationEditNameState : public RoomControlState, private ControlContainer
{ 
    private:
      Label titleLabel;  
      TextBox nameTextBox;  
      Icon  moveLeftIcon;
      Icon  moveRightIcon;
      Icon  selectIcon;
      ButtonBar menuButtonBar;
      
      ConfigurationEditNameState();     
      
      void draw(U8GLIB_SH1106_128X64 *u8g);


    public:
      static ConfigurationEditNameState* Instance();
      void enter(RoomControl* rc);
      void onLeftButtonClick(RoomControl* rc);
      void onRightButtonClick(RoomControl* rc);
      void onTwoButtonsClick(RoomControl* rc);

};


#endif