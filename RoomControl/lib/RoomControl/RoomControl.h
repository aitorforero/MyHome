#ifndef _RoomControl_h
#define _RoomControl_h


#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <State.h>
#include <StateMachine.h>
#include <U8glib.h>
#include <DebugUtils.h>



class RoomControl {
    public:
        static RoomControl* Instance();
        void loop();
        U8GLIB_SH1106_128X64 *u8g;
        EthernetClient* ethClient;
        void changeState(State<RoomControl>* s);
        void println(const char* text);
       
   
    private:
        RoomControl();
        char buffer[5][81];
        int line = 0;
        StateMachine<RoomControl>* mStateMachine;
};
#endif
