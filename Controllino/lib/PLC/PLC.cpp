#define CONTROLLINO_MEGA
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <Controllino.h>
#include <Button.h>
#include <Timer.h>
#include <FastDelegate.h>
#include <DebugUtils.h>

#include "PLC.h"


#define USE_MQTT
#define USE_ETHERNET
#define USE_INPUTS

#define INVALID_VALUE -99

byte mac[]  = {0x1A, 0x6B, 0xE7, 0x45, 0xB9, 0x26};
IPAddress ip(192, 168, 1, 20);
IPAddress server(192, 168, 1, 10);
const char* root_Topic = "casa";
const char* PLC_Topic = "N2";
const char* command_Topic = "command";
const char* state_Topic = "state";
const char* log_Topic = "casa/log/N2";
const char* subscribe_Topic = "casa/N2/#";
bool ON = false;

EthernetClient PLC::ethClient;
PubSubClient PLC::mqttClient(ethClient);
List<Input*> PLC::inputs;

void PLC::setup() {

  DEBUG_PRINT("Inicializando PLC");
   
#ifdef USE_MQTT
  PLC::initializeMQTT();
#endif
#ifdef USE_ETHERNET
  PLC::initializeEthernet();
#endif
#ifdef USE_INPUTS
  PLC::initializeInputs();
#endif
    
  DEBUG_PRINT("PLC inicializado");

}
 
void PLC::loop() {
    DEBUG_PRINT("loop start");
 #ifdef USE_MQTT
    bool connected  = true;

    if (!mqttClient.connected()) {
        connected = reconnect();
    }
    
    if (connected) mqttClient.loop();
#endif
#ifdef USE_INPUTS
    Timer::loop();
#endif
    DEBUG_PRINT("loop end");
}

void PLC::initializeMQTT() {
  INFO_PRINT("Inicializando cliente MQTT...");
  PLC::mqttClient.setServer(server, 1883);
  PLC::mqttClient.setCallback(PLC::onMQTTMessage);
}

void PLC::initializeEthernet() {
  INFO_PRINT("Inicializando ethernet...");
  Ethernet.begin(mac,ip);
  // Allow the hardware to sort itself out
  delay(1500);
}

void PLC::initializeInputs() {  
  	INFO_PRINT("Inicializando entradas...");
	
/*	Button * newButton = new Button(CONTROLLINO_A0 , LOW, true, &PLC::onButtonClick, 10);
	Input * newInput = new Input("A0", newButton);
	PLC::inputs.add(newInput);
	
	*/
	PLC::inputs.add(new Input("A0", new Button(CONTROLLINO_A0 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A1", new Button(CONTROLLINO_A1 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A2", new Button(CONTROLLINO_A2 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A3", new Button(CONTROLLINO_A3 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A4", new Button(CONTROLLINO_A4 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A5", new Button(CONTROLLINO_A5 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A6", new Button(CONTROLLINO_A6 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A7", new Button(CONTROLLINO_A7 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A8", new Button(CONTROLLINO_A8 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A9", new Button(CONTROLLINO_A9 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A10", new Button(CONTROLLINO_A10 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A11", new Button(CONTROLLINO_A11 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A12", new Button(CONTROLLINO_A12 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A13", new Button(CONTROLLINO_A13 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A14", new Button(CONTROLLINO_A14 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A15", new Button(CONTROLLINO_A15 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("I16", new Button(CONTROLLINO_I16 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("I17", new Button(CONTROLLINO_I17 , LOW, true, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("I18", new Button(CONTROLLINO_I18 , LOW, true, &PLC::onButtonClick, 10)));
	
}

bool PLC::reconnect() {
    bool res;
    // Loop until we're reconnected
    INFO_PRINT("Conectando con servidor MQTT...");
    // Attempt to connect
    if (mqttClient.connect(PLC_Topic)) {
      // Once connected, publish an announcement...
        log("Conectado!");
        // ... and resubscribe
        mqttClient.subscribe(subscribe_Topic);
        INFO_PRINT("Suscrito a: ");
        INFO_PRINT(subscribe_Topic); 
        res = true;
    } else {
        INFO_PRINT("Error!, rc=");
        INFO_PRINT(mqttClient.state());
        INFO_PRINT(" reintentando en 5 segundos");
        // Wait 5 seconds before retrying
        delay(5000);
        res = false;
    }
    return res;
}

void PLC::log(const char* errorMsg)
{
    INFO_PRINT(errorMsg);
    if (mqttClient.connected()) {
         mqttClient.publish(log_Topic, errorMsg);
    }
}

void PLC::onMQTTMessage(char* topic, byte* payload, unsigned int length) {
    DEBUG_PRINT("Message arrived [");
    DEBUG_PRINT(topic);
    DEBUG_PRINT("] ");
    for (int i=0;i<length;i++) {
        DEBUG_PRINT((char)payload[i]);
    }
    DEBUG_PRINT();

    char command[10];
    if (getOuput(topic, command)) {
        DEBUG_PRINT("Comando: ");
        DEBUG_PRINT(command);
        int newState = getValue(payload, length);
        
        if(command[0]=='R') {
            updateRelay(command, newState);
        }

  } else {
      DEBUG_PRINT("Mensaje de estado");
  }
}


bool PLC::getOuput(char* topic,char* ouput) {
    String sTopic(topic);
    if(!sTopic.endsWith(command_Topic)) {
        return false;
    }
    
    String sOutput = sTopic.substring(strlen(subscribe_Topic)-1);
    sOutput = sOutput.substring(0,sOutput.indexOf("/"));
  
    sOutput.toCharArray(ouput, sOutput.length()+1);
    return true;
}

void PLC::updateRelay(char* relayName,int newState) {
    String strRelayName(relayName);
    int relayNumber = strRelayName.substring(1).toInt();
    if(relayNumber>=0 && relayNumber<16) {
        int relayPort = CONTROLLINO_RELAY_00 + relayNumber;
		pinMode(relayPort,OUTPUT);
        digitalWrite(relayPort, newState);

		char value[2];
        itoa(newState,value,10);
		PLC::publish(relayName, "state", value);
    } else {
        log("Numero de rele incorrecto");
    }

}

void PLC::publish(const char* portName,const char* messageType, const char* payload ){
	// Create message topic
	String topicString = String(root_Topic);
	topicString += String("/");
	topicString += String(PLC_Topic);
	topicString += String("/");
	topicString += String(portName);
	topicString += String("/");
	topicString += String(messageType);
	
	int topicLength = topicString.length()+1;

	char topic[topicLength];
	topicString.toCharArray(topic, topicLength); 

	mqttClient.publish(topic, payload);  
}

void PLC::onButtonClick(EventArgs* e){
	INFO_PRINT("Click!!!");
	INFO_PRINT(((Button*)e->sender)->pin());
	
	int i;
	for(i=0;i<PLC::inputs.count();i++) {
		Input* current = inputs.item(i);
		if (current->button->pin()==((Button*)e->sender)->pin()) {
			INFO_PRINT(current->topic);
			PLC::publish(current->topic, "command", "click");
			break;
		}
	}
}






int PLC::getValue(byte* payload, unsigned int length) {
    int value = INVALID_VALUE;
    if (length==1) {
        switch (payload[0]-'0') {
            case 0:
                value = LOW;
                break;
            case 1:
                value = HIGH;
                break;
            default:
                log("Error valor mensaje");
                break;
        }
    }  else  {
        log("Error en formato del mensaje");
    }
    
    return value;
}
