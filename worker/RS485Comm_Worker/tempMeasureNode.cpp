
#include "TempMeasureNode.h"


//
// Define the temp measure peripheral
//

tempMeasureDevice::tempMeasureDevice(){
  
}

void tempMeasureDevice::getRegisterDescription(int registerNumber, simpleBuffer spb){
    if (registerNumber < REGISTER_START_NUMBER) { deviceDefinition::getRegisterDescription(registerNumber, spb); return; }
}

int tempMeasureDevice::getRegisterIntegerValue(int registerNumber) {
  if (registerNumber == REGISTER_DEVICE_REGISTER_LAST_ID) return 3;
}

//
// Building the node
//

tempMeasureNode::tempMeasureNode(){
  nodeDefinition();
  
}

deviceDefinition* tempMeasureNode::getDevice(int deviceNumber){
  if (deviceNumber == 1) return &myDevice[0];
  if (deviceNumber == 2) return &myDevice[1];
  
  return nodeDefinition::getDevice(deviceNumber);
}

int tempMeasureNode::getLastDeviceID(){
  return 2;
}
