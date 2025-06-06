
#include "NodeDefinition.h"

#define MAX_ADDRESS 63
#define EEPROMAddress_DeviceID 1

nodeDefinition::nodeDefinition(){
  _NodeAddr = EEPROM.read(EEPROMAddress_DeviceID);
}

bool  nodeDefinition::validNodeAddress(int addr){
  return ((1 <= addr) && (addr <= MAX_ADDRESS));
}
    
void nodeDefinition::setNodeAddress(int addr){
  if ((1 <= addr) && (addr <= MAX_ADDRESS)) {
      EEPROM.write(EEPROMAddress_DeviceID, addr);
      _NodeAddr = addr;
  }
  else return;
}

int nodeDefinition::nodeAddr(){
  return _NodeAddr;
}

void nodeDefinition::setFlashLedMode(bool mode){
  _FlashLedMode = mode;
}
    
bool nodeDefinition::getFlashLedMode(){
  return _FlashLedMode;
}


void nodeDefinition::gettNodeRegisterDescription(int registerNumber){
  ;
}

void nodeDefinition::getDeviceRegisterDescription(int deviceNumber, int registerNumber){
  ;
}

void nodeDefinition::gettNodeRegisterValue(int registerNumber){
  ;
}

void nodeDefinition::getDeviceRegisterValue(int deviceNumber, int registerNumber){
  ;
}

void nodeDefinition::settNodeRegisterValue(int registerNumber){
  ;
}

void nodeDefinition::setDeviceRegisterValue(int deviceNumber, int registerNumber){
  ;
}
