
#include "TempMeasureNode.h"


//
// Define the temp measure peripheral
//

tempMeasureDevice::tempMeasureDevice(){
  
}

void tempMeasureDevice::getRegisterDescription(int registerNumber, char v[], int bufferLength){
  
}

int tempMeasureDevice::getRegisterIntegerValue(int registerNumber) {
  if (registerNumber == REGISTER_DEVICE_REGISTER_COUNT) return 3;
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
