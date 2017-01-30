#ifndef _Configuration_h
#define _Configuration_h

#define CONFIGURATION_ADDRESS 0x0;
#define CONFIGURATION_SIGNATURE 0xff5753

class Configuration
{
  public:
    static bool isPresent();
    
    static char* getMACAddress();
    static void setMACAddress(char* newAddress);

};







#endif