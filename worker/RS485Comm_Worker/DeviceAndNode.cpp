
#include "DeviceAndNode.h"

#define MAX_ADDRESS 63
#define EEPROMAddress_DeviceID 1


// Node definition
nodeDefinition::nodeDefinition(){
  _NodeAddr = EEPROM.read(EEPROMAddress_DeviceID);

  // update nbr device in _baseDevice
  _baseDevice.setLastDeviceID(getLastDeviceID());
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

int nodeDefinition::getNodeAddr(){
  return _NodeAddr;
}

void nodeDefinition::setFlashLedMode(bool mode){
  _FlashLedMode = mode;
}
    
bool nodeDefinition::getFlashLedMode(){
  return _FlashLedMode;
}


void nodeDefinition::getRegisterDescription(int deviceNumber, int registerNumber, simpleBuffer spb){
  deviceDefinition* temp = getDevice(deviceNumber);
  temp->getRegisterDescription(registerNumber, spb);
  ;
}


void nodeDefinition::getRegisterValue(int deviceNumber, int registerNumber){
  ;
}

    
void nodeDefinition::setRegisterValue(int deviceNumber, int registerNumber){
  ;
}

deviceDefinition* nodeDefinition::getDevice(int deviceNumber){
  if (deviceNumber == NODE_DEVICE_ID) return &_baseDevice
  ;
}

int nodeDefinition::getLastDeviceID(){
  return 0;
}



// DEVICE

int moveToBuffer(char inBuffer[], char outBuffer[], int outBufferSize){
    int i;
   for (i=0; inBuffer[i] != 0; i++) outBuffer[i] = inBuffer[i];
   outBuffer[i] = 0;
   return  i; 
}

void clearBuffer(char v[], int bufferLength){
  int i;
  for (i=0; i< bufferLength; i++) v[i]=0;  
}

deviceDefinition::deviceDefinition(){

}


void deviceDefinition::configureDevice(){
  
}


void deviceDefinition::getRegisterDescription(int registerNumber, simpleBuffer spb){
  spb.clearBuffer();

  if (registerNumber == REGISTER_DEVICE_NAME) {
    setRegisterDescription( registerNumber, "-", REGISTER_DATA_TYPE_RO_STR, "NAME",  spb);
    return;
  }

  if (registerNumber == REGISTER_MODEL_ID) {
    setRegisterDescription( registerNumber, "-", REGISTER_DATA_TYPE_RO_STR, "MODEL-ID", spb);
    return;
  }


  if (registerNumber == REGISTER_DEVICE_BRAND) {
    setRegisterDescription( registerNumber, "-", REGISTER_DATA_TYPE_RO_STR, "BRAND", spb);
    return;
  }
  
  if (registerNumber == REGISTER_DEVICE_REGISTER_LAST_ID) {
    setRegisterDescription( registerNumber, "-", REGISTER_DATA_TYPE_RO_HEXINT2CHAR, "LAST-REG-ID", spb);
    return;
  }

  setRegisterDescription(registerNumber, "-", REGISTER_DATA_TYPE_ERROR, "NOT-FOUND", spb);
  return;
  
}


void deviceDefinition::getRegisterValue(int registerNumber, simpleBuffer spb){

}


void deviceDefinition::setRegisterValue(int registerNumber, simpleBuffer spb){
  
}


int deviceDefinition::getRegisterIntegerValue(int registerNumber){
  
}
    
int deviceDefinition::setRegisterIntegerValue(int registerNumber){
  
} 

void deviceDefinition::getModelID(simpleBuffer spb) {
    getRegisterValue(REGISTER_MODEL_ID, spb);
}


void deviceDefinition::getName(simpleBuffer spb){
    getRegisterValue(REGISTER_DEVICE_NAME, spb);
}


int deviceDefinition::getRegisterLastID(){
  return getRegisterIntegerValue(REGISTER_DEVICE_REGISTER_LAST_ID);
}


#define DESC_OFFSET_REG_NUMBER 0
#define DESC_OFFSET_UOM 2
#define DESC_OFFSET_RW_MODE 6
#define DESC_OFFSET_LABEL 7
#define DESC_OFFSET_MAX 15


void deviceDefinition::setRegisterDescription(int registerNumber, char UoM[], char mode, char label[], simpleBuffer spb){
 spb.setHexByteAt(DESC_OFFSET_REG_NUMBER, registerNumber);
 spb.moveChars(DESC_OFFSET_UOM, UoM, 3);
 spb.setCharAt(DESC_OFFSET_RW_MODE, mode);
 spb.moveChars(DESC_OFFSET_LABEL, label, 10);
 return;
}


//
// Node information device (device 00 )
//
nodeInfoDeviceDefinition::nodeInfoDeviceDefinition(){
  _lastError = 0;
}
    
void nodeInfoDeviceDefinition::configureDevice(){
  
}

void nodeInfoDeviceDefinition::setLastDeviceID(int lastDeviceID){
  _lastDeviceID = lastDeviceID;
}

void nodeInfoDeviceDefinition::setLastError(int lastError){
  _lastError = lastError;
}
    
int nodeInfoDeviceDefinition::getRegisterIntegerValue(int registerNumber) {
  if (registerNumber == REGISTER_DEVICE_REGISTER_LAST_ID) return 5;
  if (registerNumber == REGISTER_NODE_INFO_LAST_DEV_ID) return _lastDeviceID;
  if (registerNumber == REGISTER_NODE_INFO_ERRORS) return _lastError;
  if (registerNumber == REGISTER_NODE_INFO_LOC_COM) return 0;
  return -1;
  
}


void nodeInfoDeviceDefinition::getRegisterDescription(int registerNumber, simpleBuffer spb){
  if (registerNumber < REGISTER_START_NUMBER) { deviceDefinition::getRegisterDescription(registerNumber, spb); return; }

  if (registerNumber == REGISTER_NODE_INFO_LAST_DEV_ID) {
    setRegisterDescription(registerNumber, "-", REGISTER_DATA_TYPE_RO_HEXINT2CHAR, "LAST-DEV-ID", spb);
    return;
  }
  
  if (registerNumber == REGISTER_NODE_INFO_ERRORS) {
    setRegisterDescription(registerNumber, "-", REGISTER_DATA_TYPE_RO_HEXINT4CHAR, "ERR-STAT", spb);
    return;
  }
  
  if (registerNumber == REGISTER_NODE_INFO_LOC_COM) {
    setRegisterDescription(registerNumber, "-", REGISTER_DATA_TYPE_RO_BOOLEAN, "LOC-COM", spb);
    return;
  }

}
