#include "customDeviceAndNode.h"

//
// Define the temperature measure peripheral
//

#define MY_DEVICE_REGISTER_TEMPERATURE CUSTOM_REGISTER_START_NUMBER + 1
#define MY_DEVICE_REGISTER_PROBE_ADDRESS CUSTOM_REGISTER_START_NUMBER + 2
#define MY_DEVICE_REGISTER_PARASITE_MODE CUSTOM_REGISTER_START_NUMBER + 3

#define MY_DEVICE_LAST_REGISTER MY_DEVICE_REGISTER_PARASITE_MODE

tempMeasureDevice::tempMeasureDevice(){
  
}

void tempMeasureDevice::getRegisterDescription(int registerNumber, simpleBuffer spb){
    // Keep this statement to handle standard registers
    if (registerNumber < CUSTOM_REGISTER_START_NUMBER) { deviceDefinition::getRegisterDescription(registerNumber, spb); return; }

    switch (registerNumber){
      case   MY_DEVICE_REGISTER_TEMPERATURE:
        storeRegisterDescriptionInBuffer(registerNumber, "°C", REGISTER_DATA_TYPE_SCALEDFLOAT, REGISTER_MODE_RO, "TEMP-C", spb);
        break;
      case MY_DEVICE_REGISTER_PROBE_ADDRESS:
        break;
      case MY_DEVICE_REGISTER_PARASITE_MODE:
        break;
      default:
      ;
    }

    return;
}

void tempMeasureDevice::getRegisterValue(int registerNumber, simpleBuffer spb) {
  float temperature;
  long int_temp = 251234; //temperature *1000;
  
  switch (registerNumber) {
  // common registers
    case REGISTER_DEVICE_NAME:
      storeRegisterValueInBuffer(registerNumber,'TEMPERATURE', spb);
      break;

    case REGISTER_MODEL_ID:
      storeRegisterValueInBuffer(registerNumber,'DALLAS-DS28XX', spb);
      break;
      
    case REGISTER_DEVICE_BRAND:
      storeRegisterValueInBuffer(registerNumber,'SL-TEST', spb);
      break;

    case REGISTER_DEVICE_REGISTER_LAST_ID:
      storeRegisterInt2ValueInBuffer(registerNumber, MY_DEVICE_LAST_REGISTER, spb);
      break;

  // device specific registers
    case MY_DEVICE_REGISTER_TEMPERATURE:
        storeRegisterInt2ValueInBuffer( registerNumber, int_temp,  spb);
        break;
    
    case MY_DEVICE_REGISTER_PROBE_ADDRESS:
        storeRegisterInt4ValueInBuffer( registerNumber, 123,  spb);
        break;
  
    case MY_DEVICE_REGISTER_PARASITE_MODE:
        storeRegisterInt2ValueInBuffer(registerNumber, 0 , spb);
        break;
        
    default:
        ;  
  }
  return;
}
  
//
// Custom node
//
// Building the node
//

customNodeDefinition::customNodeDefinition(){
  // Init the parent node
  nodeDefinition();

  // Add code to init the node
  
}
void customNodeDefinition::configureCustomNode(){

  nodeDefinition::configureCommonNode();
}

deviceDefinition* customNodeDefinition::getDevice(int deviceNumber){
  switch (deviceNumber) {
    case MYDEVICE_1:
      return &myDevice1;
    case MYDEVICE_2:
      return &myDevice2;
    default:
       return nodeDefinition::getDevice(deviceNumber);
  } 
}

int customNodeDefinition::getLastDeviceID(){
  return LAST_DEVICE_ID;
}
