#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>

#define CONFIG_SIGNATURE "RCtrl00"
#define CONFIG_SIGNATURE_LENGTH 7
#define CONFIG_MAX_LENGTH 100

namespace Configuration {
     enum States {
        undefinedState, 
        initialState, 
        menuState, 
        PLCTopicState,
        MACState,
        IPState,
        serverState,
        portState,
        rootTopicState,
        commandTopicState,
        stateTopicState,
        logTopicState
    };
    
    extern byte mac[6];
    extern bool isValid;
    extern bool isConfiguring;
    extern char signature[CONFIG_SIGNATURE_LENGTH+1];
    
    void initial(String readedString);
    void menu(String readedString);
    void MAC(String readedString);
    void setMenuState();
    void setInitialState();
    void setMACState();
    void loop();
    
    void save();
    void saveCharArray(int &offset, char* charArray);
    void saveByteArray(int &offset, byte* byteArray, int length);
    void load();
    void readCharArray(int &offset, char* charArray, int maxLength);
    void saveByteArray(int &offset, byte* byteArrayv, int length);
}

#endif