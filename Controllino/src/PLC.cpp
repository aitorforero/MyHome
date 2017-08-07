#define CONTROLLINO_MEGA
#include <Arduino.h>
#include <Controllino.h>
#undef SPI_HAS_EXTENDED_CS_PIN_HANDLING
#include <Ethernet.h>
#include <SPI.h>
#include <PubSubClient.h>
#include <Button.h>
#include <Timer.h>
#include <FastDelegate.h>
#include <DebugUtils.h>
#include <List.h>
#include "Configuration.h"
#include "PLC.h"


#define INVALID_VALUE -99





EthernetClient PLC::ethClient;
PubSubClient PLC::mqttClient(ethClient);
List<Input*> PLC::inputs;
long PLC::millisLastAttempt = 0;

void PLC::setup() {

	DEBUG_PRINT("Inicializando PLC");

	Configuration::load();	

	if(Configuration::isValid) {
		PLC::initializeMQTT();
		PLC::initializeEthernet();
		PLC::initializeInputs();
	} else {
		INFO_PRINT("PLC sin configurar");
	}
	DEBUG_PRINT("PLC inicializado");

}
 
void PLC::loop() {
    DEBUG_PRINT("loop start");
	
	Configuration::loop();
	
	if(Configuration::isValid && !Configuration::isConfiguring) {
		bool connected  = true;

		if (!mqttClient.connected() && (millisLastAttempt ==0 || ((millis() - millisLastAttempt) >= 5000))) {
			millisLastAttempt = millis();
			connected = reconnect();
		}

		if (connected) {
			mqttClient.loop();
		}  else {
			INFO_PRINT("Reintentando dentro de cinco segun");
		}
		Timer::loop();
	}
	
    DEBUG_PRINT("loop end");
}

void PLC::initializeMQTT() {
  INFO_PRINT("Inicializando cliente MQTT...");
  IPAddress server(Configuration::server[0], Configuration::server[1], Configuration::server[2], Configuration::server[3]);
  PLC::mqttClient.setServer(server, Configuration::port);
  PLC::mqttClient.setCallback(PLC::onMQTTMessage);
}

void PLC::initializeEthernet() {
  INFO_PRINT("Inicializando ethernet...");
  IPAddress ip(Configuration::ip[0], Configuration::ip[1], Configuration::ip[2], Configuration::ip[3]);
  Ethernet.begin(Configuration::mac,ip);
  // Allow the hardware to sort itself out
  delay(1500);

    Serial.println(Ethernet.localIP());
	
}

void PLC::initializeInputs() {  
  	INFO_PRINT("Inicializando entradas...");
	
	PLC::inputs.add(new Input("A0", new Button(CONTROLLINO_A0 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A1", new Button(CONTROLLINO_A1 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A2", new Button(CONTROLLINO_A2 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A3", new Button(CONTROLLINO_A3 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A4", new Button(CONTROLLINO_A4 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A5", new Button(CONTROLLINO_A5 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A6", new Button(CONTROLLINO_A6 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A7", new Button(CONTROLLINO_A7 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A8", new Button(CONTROLLINO_A8 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A9", new Button(CONTROLLINO_A9 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A10", new Button(CONTROLLINO_A10 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A11", new Button(CONTROLLINO_A11 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A12", new Button(CONTROLLINO_A12 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A13", new Button(CONTROLLINO_A13 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A14", new Button(CONTROLLINO_A14 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("A15", new Button(CONTROLLINO_A15 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("I16", new Button(CONTROLLINO_I16 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("I17", new Button(CONTROLLINO_I17 , HIGH, false, &PLC::onButtonClick, 10)));
	PLC::inputs.add(new Input("I18", new Button(CONTROLLINO_I18 , HIGH, false, &PLC::onButtonClick, 10)));
	INFO_PRINT("Entradas inicializadas: ");
}

bool PLC::reconnect() {
    bool res;
    // Loop until we're reconnected
    INFO_PRINT("Conectando con servidor MQTT...");
    // Attempt to connect
    if (mqttClient.connect(Configuration::PLC_Topic)) {
      // Once connected, publish an announcement...
        log("Conectado!");
        // ... and resubscribe
		int topicLength = strlen(Configuration::root_Topic) +  strlen(Configuration::PLC_Topic)+4;
		char subscribe_Topic[topicLength]; 
        sprintf(subscribe_Topic, "%s/%s/#", Configuration::root_Topic, Configuration::PLC_Topic);
        mqttClient.subscribe(subscribe_Topic);
        INFO_PRINT("Suscrito a: ");
        INFO_PRINT(subscribe_Topic); 
        res = true;
    } else {
        INFO_PRINT("Error!, rc=");
        INFO_PRINT(mqttClient.state());
        //INFO_PRINT(" reintentando en 5 segundos");
        // Wait 5 seconds before retrying
        //delay(5000);
        res = false;
    }
    return res;
}

void PLC::log(const char* errorMsg)
{
    INFO_PRINT(errorMsg);
    if (mqttClient.connected()) {
		int topicLength = strlen(Configuration::root_Topic) +  strlen(Configuration::log_Topic)+ strlen(Configuration::PLC_Topic)+3;
		char log_Topic[topicLength]; 
        sprintf(log_Topic, "%s/%s/%s", Configuration::root_Topic, Configuration::log_Topic, Configuration::PLC_Topic);
        mqttClient.publish(log_Topic, errorMsg);
    }
}

void PLC::onMQTTMessage(char* topic, byte* payload, unsigned int length) {
    DEBUG_PRINT("Message arrived [");
    DEBUG_PRINT(topic);
    DEBUG_PRINT("] ");
    for (unsigned int i=0;i<length;i++) {
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
    if(!sTopic.endsWith(Configuration::command_Topic)) {
        return false;
    }
	int topicLength = strlen(Configuration::root_Topic) +  strlen(Configuration::PLC_Topic)+4;
	char subscribe_Topic[topicLength]; 
	sprintf(subscribe_Topic, "%s/%s/#", Configuration::root_Topic,  Configuration::PLC_Topic);
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
		PLC::publish(relayName, Configuration::state_Topic, value);
    } else {
        log("Numero de rele incorrecto");
    }

}

void PLC::publish(const char* portName,const char* messageType, const char* payload ){
	// Create message topic
	String topicString = String(Configuration::root_Topic);
	topicString += String("/");
	topicString += String(Configuration::PLC_Topic);
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
       DEBUG_PRINT("Comando ignorado");
    }
    
    return value;
}
