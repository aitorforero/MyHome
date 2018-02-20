#ifndef _ConfigurationEditPortState_h
#define _ConfigurationEditPortState_h


#include "RoomControl.h"
#include "RoomControlState.h"
#include "Controls/Label.h"
#include "Controls/Icon.h"
#include "Controls/ButtonBar.h"
#include "Controls/TextBox.h"

#define NAME_LENGTH 8

class ConfigurationEditPortState : public RoomControlState, private ControlContainer
{ 
    private:
      Label titleLabel;  
      TextBox portTextBox;  
      Icon  moveLeftIcon;
      Icon  moveRightIcon;
      Icon  selectIcon;
      ButtonBar menuButtonBar;

      void draw(U8GLIB_SH1106_128X64 *u8g);


    public:
      ConfigurationEditPortState(RoomControl* rc);     
      void onEnter();
      void onExit();
      const char * getName();
     
      void handleButtonClick(ButtonEventArgs* e);
};


#endif
