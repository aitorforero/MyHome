#ifndef _RoomControl_h
#define _RoomControl_h


#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <StateMachine.h>

#include <DebugUtils.h>


class RoomControl {
    public:
        void setup();
        void loop();
        static RoomControl* Instance();
   
    private:
        static RoomControl* _instance;
        StateMachine<RoomControl>* mStateMachine;
        EthernetClient ethClient;
        void initializeEthernet();
};
#endif
