
#include "DeviceAndNode.h"

#define MAX_ADDRESS 63
#define EEPROMAddress_DeviceID 1

//
// Generic Node definition
//
nodeDefinition::nodeDefinition(){
  _NodeAddr = EEPROM.read(EEPROMAddress_DeviceID);
  _baseDevice.myNode = this;
  
 
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
  if (temp == NULL) return ;
  temp->getRegisterDescription(registerNumber, spb);
  
}


void nodeDefinition::getRegisterValue(int deviceNumber, int registerNumber, simpleBuffer spb){
  deviceDefinition* temp = getDevice(deviceNumber);
  if (temp == NULL) return ;
  temp->getRegisterValue(registerNumber, spb); 
  
}

    
void nodeDefinition::setRegisterValue(int deviceNumber, int registerNumber, simpleBuffer spb){
  deviceDefinition* temp = getDevice(deviceNumber);
  if (temp == NULL) return ;
  
}

deviceDefinition* nodeDefinition::getDevice(int deviceNumber){
  if (deviceNumber == NODE_INFO_DEVICE_ID) return &_baseDevice;
  return NULL;
}

int nodeDefinition::getLastDeviceID(){
  return _lastDeviceID;
}


void nodeDefinition::configureCommonNode(){
  
}

// 
// Generic device definition
//

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

//
// Describe the registers expected in all devices
//
void deviceDefinition::getRegisterDescription(int registerNumber, simpleBuffer spb){
  spb.clearBuffer();

  if (registerNumber == REGISTER_DEVICE_NAME) {
    storeRegisterDescriptionInBuffer( registerNumber, "-", REGISTER_DATA_TYPE_STR, REGISTER_MODE_RO, "NAME",  spb);
    return;
  }

  if (registerNumber == REGISTER_MODEL_ID) {
    storeRegisterDescriptionInBuffer( registerNumber, "-", REGISTER_DATA_TYPE_STR, REGISTER_MODE_RO, "MODEL-ID", spb);
    return;
  }


  if (registerNumber == REGISTER_DEVICE_BRAND) {
    storeRegisterDescriptionInBuffer( registerNumber, "-", REGISTER_DATA_TYPE_STR, REGISTER_MODE_RO, "BRAND", spb);
    return;
  }
  
  if (registerNumber == REGISTER_DEVICE_REGISTER_LAST_ID) {
    storeRegisterDescriptionInBuffer( registerNumber, "-", REGISTER_DATA_TYPE_HEXINT2CHAR, REGISTER_MODE_RO, "LAST-REG-ID", spb);
    return;
  }

  if (registerNumber == REGISTER_DEVICE_ACTIVE) {
    storeRegisterDescriptionInBuffer( registerNumber, "-", REGISTER_DATA_TYPE_BOOLEAN, REGISTER_MODE_RO, "ACTIVE", spb);
    return;    
  }
  
  storeRegisterDescriptionInBuffer(registerNumber, "-", REGISTER_DATA_TYPE_ERROR, REGISTER_MODE_ERROR, "NOT-FOUND", spb);
  return;
  
}


void deviceDefinition::getRegisterValue(int registerNumber, simpleBuffer spb){
  spb.clearBuffer();
  return;
}


void deviceDefinition::setRegisterValue(int registerNumber, simpleBuffer spb){
  
}

 
#define DESC_OFFSET_REG_NUMBER 0
#define DESC_OFFSET_UOM 2
#define DESC_OFFSET_RW_MODE 6
#define DESC_OFFSET_DATATYPE 7
#define DESC_OFFSET_LABEL 8
#define DESC_OFFSET_MAX 15

#define DESC_LEN_UOM 3
#define DESC_LEN_LABEL 8

void deviceDefinition::storeRegisterDescriptionInBuffer(int registerNumber, char UoM[], char datatype, char mode, char label[], simpleBuffer spb){
 spb.setHexByteAt(DESC_OFFSET_REG_NUMBER, registerNumber);
 spb.moveChars(DESC_OFFSET_UOM, UoM, DESC_LEN_UOM);
 spb.setCharAt(DESC_OFFSET_RW_MODE, mode);
 spb.setCharAt(DESC_OFFSET_DATATYPE, datatype);
 spb.moveChars(DESC_OFFSET_LABEL, label, DESC_LEN_LABEL);
 return;
}

#define VAL_OFFSET_REG_NUMBER 0
#define VAL_OFFSET_DATATYPE 2
#define VAL_OFFSET_VALUE 3
#define VAL_OFFSET_MAX 15

#define VAL_LEN_VALUE 10

void deviceDefinition::storeRegisterNoValueInBuffer(int registerNumber, simpleBuffer spb){
  spb.setHexByteAt(VAL_OFFSET_REG_NUMBER, registerNumber);
  spb.setCharAt(VAL_OFFSET_DATATYPE, REGISTER_DATA_TYPE_ERROR);
  spb.setCharAt(VAL_OFFSET_VALUE, REGISTER_DATA_TYPE_ERROR);
}
    
void deviceDefinition::storeRegisterValueInBuffer(int registerNumber, char value[], simpleBuffer spb){
  spb.setHexByteAt(VAL_OFFSET_REG_NUMBER, registerNumber);
  spb.setCharAt(VAL_OFFSET_DATATYPE, REGISTER_DATA_TYPE_STR);  
  spb.moveChars(VAL_OFFSET_VALUE, value, VAL_LEN_VALUE);
}

void deviceDefinition::loadRegisterValueFromBuffer(int registerNumber,  simpleBuffer spb){
  
}

void deviceDefinition::storeRegisterBoolValueInBuffer(int registerNumber, bool value, simpleBuffer spb){
  spb.setHexByteAt(VAL_OFFSET_REG_NUMBER, registerNumber);
  spb.setCharAt(VAL_OFFSET_DATATYPE, REGISTER_DATA_TYPE_BOOLEAN); 
  spb.setCharAt(VAL_OFFSET_VALUE, (value ? '1':'0'));
}

void deviceDefinition::storeRegisterInt2ValueInBuffer(int registerNumber, int value, simpleBuffer spb){
  spb.setHexByteAt(VAL_OFFSET_REG_NUMBER, registerNumber);
  spb.setCharAt(VAL_OFFSET_DATATYPE, REGISTER_DATA_TYPE_HEXINT2CHAR); 
  spb.setHexByteAt(VAL_OFFSET_VALUE, value);
}

void deviceDefinition::loadRegisterInt2ValueFromBuffer(int registerNumber, simpleBuffer spb){

}

void deviceDefinition::storeRegisterInt4ValueInBuffer(int registerNumber, int value, simpleBuffer spb){
  spb.setHexByteAt(VAL_OFFSET_REG_NUMBER, registerNumber);
  spb.setCharAt(VAL_OFFSET_DATATYPE, REGISTER_DATA_TYPE_HEXINT4CHAR); 
  spb.setHexDigitsAt(VAL_OFFSET_VALUE, value, 4);
}


void deviceDefinition::storeRegisterScaledFloatValueInBuffer(int registerNumber, long value, simpleBuffer spb){
  spb.setHexByteAt(VAL_OFFSET_REG_NUMBER, registerNumber);
  spb.setCharAt(VAL_OFFSET_DATATYPE, REGISTER_DATA_TYPE_SCALEDFLOAT);    
  spb.setSignedHexDigitsAt(VAL_OFFSET_VALUE, value, 8);
}


void deviceDefinition::loadRegisterInt4ValueFromBuffer(int registerNumber, simpleBuffer spb){

}


//
// Node information device (device 00 )
//
nodeInfoDeviceDefinition::nodeInfoDeviceDefinition(){
  _lastError = 0;
}
    
void nodeInfoDeviceDefinition::configureDevice(){
  
}
 

void nodeInfoDeviceDefinition::setLastError(int lastError){
  _lastError = lastError;
}
    
 
void nodeInfoDeviceDefinition::getRegisterDescription(int registerNumber, simpleBuffer spb){
  if (registerNumber < CUSTOM_REGISTER_START_NUMBER) { deviceDefinition::getRegisterDescription(registerNumber, spb); return; }
  
  switch (registerNumber) {
    
    case REGISTER_NODE_INFO_LAST_DEV_ID:
        storeRegisterDescriptionInBuffer(registerNumber, "-", REGISTER_DATA_TYPE_HEXINT2CHAR, REGISTER_MODE_RO, "LAST-DEV-ID", spb);
        break;
    
    case REGISTER_NODE_INFO_ERRORS:
        storeRegisterDescriptionInBuffer(registerNumber, "-", REGISTER_DATA_TYPE_HEXINT4CHAR, REGISTER_MODE_RO, "ERR-STAT", spb);
        break;
  
    case REGISTER_NODE_INFO_LOC_COM:
        storeRegisterDescriptionInBuffer(registerNumber, "-", REGISTER_DATA_TYPE_BOOLEAN, REGISTER_MODE_RO, "LOC-COM", spb);
        break;
        
    default:
        storeRegisterDescriptionInBuffer(registerNumber, "-", REGISTER_DATA_TYPE_ERROR, REGISTER_MODE_ERROR, "ERROR", spb);  
  }
  
  return;
   
}



void nodeInfoDeviceDefinition::getRegisterValue(int registerNumber, simpleBuffer spb){
  
  switch (registerNumber) {
  // common registers
    case REGISTER_DEVICE_NAME:
      storeRegisterValueInBuffer(registerNumber,myNode->nodeName, spb);
      break;

    case REGISTER_MODEL_ID:
      storeRegisterValueInBuffer(registerNumber,myNode->nodeModel, spb);
      break;
      
    case REGISTER_DEVICE_BRAND:
      storeRegisterValueInBuffer(registerNumber,myNode->nodeBrand, spb);
      break;

    case REGISTER_DEVICE_REGISTER_LAST_ID:
      storeRegisterInt2ValueInBuffer( registerNumber, NODE_INFO_DEVICE_LAST_REGISTER, spb);
      break;

  // device specific registers
    case REGISTER_NODE_INFO_LAST_DEV_ID:
        storeRegisterInt2ValueInBuffer( registerNumber, myNode->getLastDeviceID(),  spb);
        break;
    
    case REGISTER_NODE_INFO_ERRORS:
        storeRegisterInt4ValueInBuffer( registerNumber, _lastError,  spb);
        break;
  
    case REGISTER_NODE_INFO_LOC_COM:
        storeRegisterBoolValueInBuffer(registerNumber, false , spb);
        break;
        
    default:
        ;  
  }
  
  return;
   

}


void nodeInfoDeviceDefinition::setRegisterValue(int registerNumber, simpleBuffer spb){
  return;
  
}
