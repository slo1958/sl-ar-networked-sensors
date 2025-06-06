
#ifndef nodeDefinition_h
#define nodeDefinition_h

#include "Arduino.h" 
#include <EEPROM.h>

class nodeDefinition{
  public:
    nodeDefinition();
    void configureNode();
    bool validNodeAddress(int addr);
    void setNodeAddress(int addr);
    int nodeAddr();
    void setFlashLedMode(bool mode);
    bool getFlashLedMode();

    void gettNodeRegisterDescription(int registerNumber);
    void getDeviceRegisterDescription(int deviceNumber, int registerNumber);
    void gettNodeRegisterValue(int registerNumber);
    void getDeviceRegisterValue(int deviceNumber, int registerNumber);
    void settNodeRegisterValue(int registerNumber);
    void setDeviceRegisterValue(int deviceNumber, int registerNumber);  

 
 protected:
    int _NodeAddr;
    int _FlashLedMode;
};


#endif
