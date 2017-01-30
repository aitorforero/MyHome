#include "HomeAutomation.h"
//#include <SPI.h>
#include <Ethernet.h>

HomeAutomation::HomeAutomation(byte* mac, char* server, int port, IPAddress ip)
{
  _mac = mac;
  _server = server;
  _ip = ip;
  _port = port;

  initialize();
}

void HomeAutomation::initialize() {
    Ethernet.begin(_mac, _ip);
    delay(1000);
    Serial.println("Ethernet ready!");
}

void HomeAutomation::raiseCommand(const char* itemName,const char* command) {
  if (client.connect(_server, _port)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.print("POST http://"); client.print(_server); client.print(":"); client.print(_port); client.print("/rest/items/"); client.print(itemName); client.println(" HTTP/1.1");
    client.print("Host: "); client.print(_server); client.print(":"); client.println(_port);
    client.print("Content-Length: "); client.println(sizeof(command));
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
