#ifndef _RoomControl_h
#define _RoomControl_h


#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <U8glib.h>
#include <DebugUtils.h>
#include <Button.h>
#include <EventArgs.h>

#include "RoomControlState.h"
#include "RoomControlStateMachine.h"
#include "ButtonEvents.h"


class RoomControl : ButtonEventsController {
    public:
        static RoomControl* Instance();
        void loop();
        U8GLIB_SH1106_128X64 *u8g;
        EthernetClient* ethClient;
        void changeState(RoomControlState* s);
        void println(const char* text);
        Button* leftButton;
        Button* rightButton; 
        void onLeftButtonClick(EventArgs* e);
        void onRightButtonClick(EventArgs* e);
        void onLeftButtonDown(EventArgs* e);
        void onRightButtonDown(EventArgs* e);
        void onLeftButtonUp(EventArgs* e);
        void onRightButtonUp(EventArgs* e);
        void reset();
      
   
    private:
        RoomControl();
        char buffer[5][81];
        int line = 0;
        RoomControlStateMachine* mStateMachine;
};
#endif
