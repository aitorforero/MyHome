#include "Configuration.h"
#include <avr/wdt.h>
#include <EEPROM.h>


   
namespace Configuration {
    
    States state = undefinedState;
    
    byte mac[6]  = {0x1A, 0x6B, 0xE7, 0x45, 0xB9, 0x26}; 
    bool isValid = false;
    bool isConfiguring = false;
    char signature[CONFIG_SIGNATURE_LENGTH+1] = CONFIG_SIGNATURE;

    
    void save() {
        int currentAddress = 0;
        saveCharArray(currentAddress, signature);
        saveByteArray(currentAddress, mac, 6);
    }
   
    void saveCharArray(int &offset, char* charArray){
        int i = 0;
        bool finish = false;
        while(!finish) {
            Serial.println(charArray[i],DEC);
            EEPROM.update(offset+i,charArray[i]);
            if(!charArray[i]) {
                finish = true;
            }
            i++;
        }
        
        offset +=i;
    }
    
    
    void saveByteArray(int &offset,byte* byteArray, int length){
        int i = 0;
        for(i=0;i<length;i++){
             EEPROM.update(offset+i,byteArray[i]);
        }
        offset +=i;
    }
    
    void readCharArray(int &offset, char* charArray, int maxLength){
        String aux("");
        int i = 0;
        bool finish = false;
        while(!finish) {
            char signatureChar = 0;
            EEPROM.get(offset+i, signatureChar);
            if(!signatureChar || i >= (maxLength-1)) {
                aux.toCharArray(charArray,i+1);
                finish = true;
            } else {
                aux += signatureChar;
            }
            i++;
        }
        
        offset +=i;
    }
    
    void readByteArray(int &offset,byte* byteArray, int length){
        int i = 0;
        for(i=0;i<length;i++){
             EEPROM.get(offset+i,byteArray[i]);
        }
        offset +=i;
    }
    
    void load() {
        Serial.print("Loading configuration...");
        int currentAddress = 0;
        char aux[CONFIG_SIGNATURE_LENGTH+1];
        isValid = true;

        // signature
        readCharArray(currentAddress, aux, CONFIG_SIGNATURE_LENGTH+1);
        if(strcmp(aux,signature)) {
            Serial.print("signature ");
            Serial.print(aux);
            Serial.print(" invalid!!!");
            isValid = false;
        } else {
            Serial.print("found...");
            readByteArray(currentAddress, mac, 6);
            Serial.println("OK");
        }
   }

    void setInitialState() {
       isConfiguring = false;
       Serial.println("Para entrar en modo configuracion pulse C");
       state = initialState;
    }
       
    void initial(String readedString) {
        if(readedString.equals(String("C"))) {
            setMenuState();
        } else {
            setInitialState();
        }
    }
    
    void setMenuState() {
        isConfiguring = true;
        Serial.println("*** MENU PRINCIPAL CONFIGURACION ***");
        Serial.println();
        
        Serial.print("1: Dirección MAC => (");
        char formatedMAC[17]; 
        sprintf(formatedMAC, "%x:%x:%x:%x:%x:%x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        Serial.print(formatedMAC);  Serial.println(")");
        
                                                 
        Serial.println();
        Serial.println("S: Salir");
        Serial.println();
        Serial.println ("Introduce opción: ");   
        state = menuState;
    }
    
    void menu(String readedString){
        if(readedString == "S") {
            setInitialState();
        } else if(readedString == "1") {   
            setMACState();
        } else if(readedString == "R") {   
              save();
              wdt_enable(WDTO_60MS);
              while(1) {}
        } else {

        }
    }
    
   void setMACState() {
        Serial.print ("Introduce MAC: (HH:HH:HH:HH:HH:HH)");   
        state = MACState;
   }  
 
   void MAC(String readedString) {
        char aux[3];
        int i;
        for(i=0;i<6;i++) {
            readedString.substring(i*3,i*3+2).toCharArray(aux,3);
            mac[i] = strtol(aux, 0, 16);
        }

        setMenuState();
    } 
    
    void loop(){
        static String readedString("");
        if (Serial.available() > 0) {
            char readed = Serial.read();
            Serial.print(readed);

            if(readed == 13){
                Serial.println();
                switch (state) {
                    case menuState:
                       menu(readedString);
                       break;
                    case initialState:
                       initial(readedString);
                       break;
                    case MACState:
                       MAC(readedString);
                       break;
                   default:
                        setInitialState();
                        break;
                }
                
                readedString="";
                Serial.print(">");
            } else {
                 readedString += readed;
            }
            
        }
    }
   
}