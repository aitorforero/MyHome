#ifndef _MainState_h
#define _MainState_h

#include <U8glib.h>
#include "Controls/ControlContainer.h"
#include "Controls/Label.h"
#include "RoomControlState.h"
#include "RoomControl.h"
class MainState : public RoomControlState, private ControlContainer
{
    public:
        MainState(RoomControl* rc);
        const char * getName();
        void execute();
        void draw(U8GLIB_SH1106_128X64 *u8g);

    private:
        long millisLastAttempt = 0;
        Label nameLabel;  
        Label textLabel;


    protected:
      void handleButtonClick(ButtonEventArgs* e);
      void handleButtonDown(ButtonEventArgs* e);
      void handleButtonUp(ButtonEventArgs* e);
      void handleMQTTMessage(MQTTMessageEventArgs* e);

};


#endif
