#define CONTROLLINO_MEGA

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <Controllino.h>
#include <Timer.h>

 

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
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

void log(const char* errorMsg)
{
    Serial.println(errorMsg);
    if (mqttClient.connected()) {
         mqttClient.publish(log_Topic, errorMsg);
    }
}

bool getOuput(char* topic,char* ouput) {
    String sTopic(topic);
    if(!sTopic.endsWith(command_Topic)) {
        return false;
    }
    
    String sOutput = sTopic.substring(strlen(subscribe_Topic)-1);
    sOutput = sOutput.substring(0,sOutput.indexOf("/"));
  
    sOutput.toCharArray(ouput, sOutput.length()+1);
    return true;
}

int getValue(byte* payload, unsigned int length) {
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

void updateRelay(char* relayName,int newState) {
    String strRelayName(relayName);
    int relayNumber = strRelayName.substring(1).toInt();
    if(relayNumber>=0 && relayNumber<16) {
        int relayPort = CONTROLLINO_RELAY_00 + relayNumber;
        digitalWrite(relayPort, newState);
        String stateTopic = String(root_Topic) + String("/") + String(PLC_Topic) + String("/") + String(relayName)+String("/state");
        char topic[(stateTopic.length()+1)];
        char value[2];
        itoa(newState,value,10);
        stateTopic.toCharArray(topic, stateTopic.length()+1); 
        mqttClient.publish(topic, value);      
    } else {
        log("Numero de rele incorrecto");
    }

}
/*
void onButtonClick(EventArgs* e){
    log("Click!");
}
*/
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i=0;i<length;i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    char command[10];
    if (getOuput(topic, command)) {
        Serial.print("Comando: ");
        Serial.println(command);
        int newState = getValue(payload, length);
        
        if(command[0]=='R') {
            updateRelay(command, newState);
        }

  } else {
      Serial.println("Mensaje de estado");
  }
}
 
bool reconnect() {
    bool res;
    // Loop until we're reconnected
    Serial.print("Conectando con servidor MQTT...");
    // Attempt to connect
    if (mqttClient.connect(PLC_Topic)) {
      // Once connected, publish an announcement...
        log("Conectado!");
        // ... and resubscribe
        mqttClient.subscribe(subscribe_Topic);
        Serial.print("Suscrito a: ");
        Serial.println(subscribe_Topic); 
        res = true;
    } else {
        Serial.print("Error!, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" reintentando en 5 segundos");
        // Wait 5 seconds before retrying
        delay(5000);
        res = false;
    }
    return res;
}


void initializeInputs()
{  
  	Serial.println("Initializing Buttons...");

//	button = new Button(CONTROLLINO_A0, LOW, true);
//    button->click()->addHandler(&onButtonClick);
    Serial.println(CONTROLLINO_A0);
}


 
void setup()
{
  Serial.begin(57600);
  Serial.println("Inicializando PLC...");
 
  mqttClient.setServer(server, 1883);
  mqttClient.setCallback(callback);
 
  Ethernet.begin(mac,ip);
  // Allow the hardware to sort itself out
  delay(1500);
}
 
void loop()
{
    bool connected  = true;
    if (!mqttClient.connected()) {
        connected = reconnect();
    }
    
    if (connected) mqttClient.loop();
    
    //Serial.println(digitalRead(CONTROLLINO_A0));
}