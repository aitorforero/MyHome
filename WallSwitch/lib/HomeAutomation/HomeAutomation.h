#ifndef _HomeAutomation_h
#define _HomeAutomation_h


#include "Arduino.h"
#include <Ethernet.h>

class HomeAutomation
{
  public:
    HomeAutomation(byte* mac, char* server, int port, IPAddress ip);
    void raiseCommand(const char* itemName,const char* command);

  private:
    byte* _mac;
    char* _server;
    IPAddress _ip;
    int _port;
    EthernetClient client;

    void initialize();
};







#endif
