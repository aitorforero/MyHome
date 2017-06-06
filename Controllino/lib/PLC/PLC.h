#ifndef _PLC_h
#define _PLC_h

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <Controllino.h>
#include <Button.h>
#include <Timer.h>

class PLC {
    public:
        static void setup();
        static void loop();
   
    private:
        static EthernetClient ethClient;
        static PubSubClient mqttClient;
        static Button* button[];
        static void initializeMQTT();
        static void initializeEthernet();
        static void initializeInputs();
        static bool reconnect();
        static void log(const char* errorMsg);
        static void onMQTTMessage(char* topic, byte* payload, unsigned int length) ;
        static bool getOuput(char* topic,char* ouput);
        static void updateRelay(char* relayName,int newState);
        static void onButtonClick(EventArgs* e);
        static int getValue(byte* payload, unsigned int length);

};
#endif
