#include <PciManager.h>
#include <PciListenerImp.h>
#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>

#define A_PIN 5
#define B_PIN 6
#define SW_PIN 7


void onA(byte);
void onB(byte);
void onSW(byte);
void onCounterClockWise();
void onClockWise();

PciListenerImp listenerA(A_PIN, onA, true);
PciListenerImp listenerB(B_PIN, onB, true);
PciListenerImp listenerSW(SW_PIN, onSW, true);

byte AValue;
byte BValue;
byte prevValue;


byte mac[] = { 0x90, 0xA2, 0xDA, 0x10, 0x91, 0x62 };
char server[] = "192.168.0.14"; 
IPAddress ip(192, 168, 0, 177);
EthernetClient client;


void initializeEthernet();

void setup() {
    wdt_disable();
    Serial.begin(9600);
    Serial.println("Initializing...");
        
    PciManager.registerListener(A_PIN, &listenerA);
    PciManager.registerListener(B_PIN, &listenerB);
    PciManager.registerListener(SW_PIN, &listenerSW);
    
    initializeEthernet();
    
    Serial.println("Ready.");
    wdt_enable(WDTO_250MS);
}

void loop() {
    wdt_reset();
}


void initializeEthernet() {
    Ethernet.begin(mac, ip);
    delay(1000);
    Serial.println("Ethernet ready!");
}

void onChange() {
    byte value = AValue * 2 + BValue;
    static int8_t enc_states[] = {0,  1, -1,  0, 
                                 -1,  0,  0,  1,
                                  1,  0,  0, -1, 
                                  0, -1,  1,  0};

    int8_t direction = enc_states[4 * value + prevValue];
    prevValue = value;
    if(direction > 0) {
        onClockWise();
    } else if(direction < 0) {
        onCounterClockWise();
    }
}

void onA(byte changeKind) {
  AValue = changeKind;
  onChange();
}

void onB(byte changeKind) {
  BValue = changeKind;
  onChange();
}

void onSW(byte changeKind) {
    if(!changeKind){
        Serial.println("Pulsado ");
    } else {
        Serial.println("Suelto");
        doGET("Light_GF_Corridor_Ceiling","ON");
    }
}

void onClockWise(){
    Serial.println("onCW");
}

void onCounterClockWise(){
    Serial.println("onCCW");
}

void doGET(char itemName[], char command[]) {
         // if you get a connection, report back via serial:
  if (client.connect(server, 8080)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.print("POST http://192.168.0.14:8080/rest/items/");
    client.print(itemName);
    client.println(" HTTP/1.1");
    client.println("Host: 192.168.0.14:8080");
    client.print("Content-Length: ");
    client.println(sizeof(command));
    client.println("Accept: application/json");
    client.println("Content-Type: text/plain");
    client.println("DNT: 1");
    client.println();
    client.println(command);
    client.println();
    
 
    
    while (!client.available()){}
    
    while (client.available()) {
        char c = client.read();
        Serial.print(c);
    }
    
    client.stop();
  }   else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }

}
