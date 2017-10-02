#ifndef _PLC_h
#define _PLC_h

#define CONTROLLINO_MEGA



#include <Arduino.h>
#include <Controllino.h>
#include <SPI.h>
#include <PubSubClient.h>
#include <Button.h>
#include <Timer.h>
#include <List.h>
#include <DebugUtils.h>

#include <Ethernet.h>


class Input {
    public:
        Button* button;
        char* topic;
        Input(const char* t, Button* b){
            this->button = b;
            this->topic = t;
        }
};


class PLC {
    public:
        static void setup();
        static void loop();
   
    private:
        static EthernetClient ethClient;
        static PubSubClient mqttClient;
        static List<Input*> inputs;
        static long millisLastAttempt;
        static void initializeMQTT();
        static void initializeEthernet();
        static void initializeInputs();
        static bool reconnect();
        static void log(const char* errorMsg);
        static void onMQTTMessage(char* topic, byte* payload, unsigned int length) ;
        static bool getOuput(char* topic,char* ouput);
        static void updateRelay(char* relayName,int newState);
        static void onButtonClick(EventArgs* e);
        static void onButtonDown(EventArgs* e);
        static void onButtonUp(EventArgs* e);
        static int getValue(byte* payload, unsigned int length);
        static void publish(const char* portName,const char* messageType, const char* payload);

};
#endif
