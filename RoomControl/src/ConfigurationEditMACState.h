#ifndef _ConfigurationEditMACState_h
#define _ConfigurationEditMACState_h


#include "RoomControl.h"
#include "RoomControlState.h"
#include "Controls/Label.h"
#include "Controls/Icon.h"
#include "Controls/ButtonBar.h"
#include "Controls/TextBox.h"

#define NAME_LENGTH 8

class ConfigurationEditMACState : public RoomControlState, private ControlContainer
{ 
    private:
      Label titleLabel;  
      TextBox MACTextBox;  
      Icon  moveLeftIcon;
      Icon  moveRightIcon;
      Icon  selectIcon;
      ButtonBar menuButtonBar;

      void draw(U8GLIB_SH1106_128X64 *u8g);


    public:
      ConfigurationEditMACState(RoomControl* rc);     
      void onEnter();
      void onExit();
      const char * getName();
     
      void handleButtonClick(ButtonEventArgs* e);
};


#endif
