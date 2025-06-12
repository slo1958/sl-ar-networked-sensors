
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


void nodeDefinition::getRegisterDescription(int deviceNumber, int registerNumber, char v[], int bufferLength){
  deviceDefinition* temp = getDevice(deviceNumber);
  temp->getRegisterDescription(registerNumber, v, bufferLength);
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


void deviceDefinition::getRegisterDescription(int registerNumber, char v[], int bufferLength){
  clearBuffer(v, bufferLength);
  
  if (registerNumber == REGISTER_DEVICE_NAME) {
    descriptionSetRegsiterNumber( registerNumber,  v);
    descriptionSetUoM("-",  v);
    descriptionSetRWMode(REGISTER_DATA_TYPE_RO_STR,  v);
    descriptionSetLabel("DEVICE",  v);
    return;
  }

  if (registerNumber == REGISTER_DEVICE_REGISTER_COUNT) {
    descriptionSetRegsiterNumber( registerNumber,  v);
    descriptionSetUoM("-",  v);
    descriptionSetRWMode(REGISTER_DATA_TYPE_RO_HEXINT2CHAR,  v);
    descriptionSetLabel("REG.COUNT",  v);
    return;
  }

  if (registerNumber == REGISTER_DEVICE_NAME) {
    
  }
    
  moveToBuffer("Undefined", v,  bufferLength);

}


void deviceDefinition::getRegisterValue(int registerNumber, char v[], int bufferLength){

}


void deviceDefinition::setRegisterValue(int registerNumber, char v[], int bufferLength){
  
}


int deviceDefinition::getRegisterIntegerValue(int registerNumber){
  
}
    
int deviceDefinition::setRegisterIntegerValue(int registerNumber){
  
} 

void deviceDefinition::getModelID(char v[], int bufferLength) {
    getRegisterValue(REGISTER_MODEL_ID, v, bufferLength);
}


void deviceDefinition::getName(char v[], int bufferLength){
    getRegisterValue(REGISTER_DEVICE_NAME, v, bufferLength);
}


int deviceDefinition::getRegisterCount(){
  return getRegisterIntegerValue(REGISTER_DEVICE_REGISTER_COUNT);
}


#define DESC_OFFSET_REG_NUMBER 0
#define DESC_OFFSET_UOM 1
#define DESC_OFFSET_RW_MODE 4
#define DESC_OFFSET_LABEL 5
#define DESC_OFFSET_MAX 15

void deviceDefinition::descriptionSetRegsiterNumber(int registerNumber, char v[]){
  v[DESC_OFFSET_REG_NUMBER] = '0' + registerNumber;
}

void deviceDefinition::descriptionSetUoM(char UoM[], char v[]){
  v[DESC_OFFSET_UOM] = UoM[0];
  v[DESC_OFFSET_UOM+1] = UoM[1];
  if (UoM[1] == 0) return;
  v[DESC_OFFSET_UOM+2] = UoM[2];
  return;
}

void deviceDefinition::descriptionSetRWMode(char mode, char v[]){
  v[DESC_OFFSET_RW_MODE] = mode;
}

void deviceDefinition::descriptionSetLabel(char label[], char v[]){
 moveToBuffer(label, v[DESC_OFFSET_LABEL],DESC_OFFSET_MAX - DESC_OFFSET_LABEL );
 return;
}


//
// Node information device (device 00 )
//
nodeInfoDeviceDefinition::nodeInfoDeviceDefinition(){
  
}
    
void nodeInfoDeviceDefinition::configureDevice(){
  
}

void nodeInfoDeviceDefinition::setLastDeviceID(int lastDeviceID){
  _lastDeviceID = lastDeviceID;
}

int nodeInfoDeviceDefinition::getRegisterIntegerValue(int registerNumber) {
  if (registerNumber == REGISTER_DEVICE_REGISTER_COUNT) return 5;
  if (registerNumber == 3) return _lastDeviceID;
  return -1;
}


#define REGISTER_DEVICE_NAME 0
#define REGISTER_MODEL_ID 1
#define REGISTER_DEVICE_REGISTER_COUNT 2

void nodeInfoDeviceDefinition::getRegisterDescription(int registerNumber, char v[], int bufferLength){
  if (registerNumber < REGISTER_START_NUMBER) { deviceDefinition::getRegisterDescription(registerNumber, v, bufferLength); return; }
  
  
  moveToBuffer("NodeInfo", v,  bufferLength);

}
