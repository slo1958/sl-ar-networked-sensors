#include "DeviceDefinition.h"

deviceDefinition::deviceDefinition(){
  ;
}


void deviceDefinition::configureDevice(){
  
}


void deviceDefinition::getRegisterDescription(int registerNumber, char v[], int bufferLength){
  if (registerNumber == 0) {
    
  } else {
    getSpecificRegisterDescription(registerNumber, v, bufferLength);
  }
}


void deviceDefinition::getSpecificDeviceRegisterValue(int registerNumber) {
  
}


void deviceDefinition::getDeviceRegisterValue(int registerNumber){
   if (registerNumber == 0) {
    
  } else {
    getSpecificDeviceRegisterValue(registerNumber);
  } 
}


void deviceDefinition::settDeviceRegisterValue(int registerNumber){
  
}


void deviceDefinition::getSpecificRegisterDescription(int registerNumber, char v[], int bufferLength){
  
}


void deviceDefinition::getDeviceModelID(char v[], int bufferLength) {
  
}


void deviceDefinition::getDeviceName(char v[], int bufferLength){
  
}


int deviceDefinition::getDeviceRegisterCount(){
  
}
