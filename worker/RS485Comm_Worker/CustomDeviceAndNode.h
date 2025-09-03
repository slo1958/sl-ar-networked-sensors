#ifndef customDeviceAndNode_h
#define customDeviceAndNode_h


#include "Arduino.h" 
#include "DeviceAndNode.h"

// Include your dependencies here

#include <OneWire.h>
#include <DallasTemperature.h>

//
// assign an id to each device
// remember device ID zero is the node information device, and should not be used here
//
// In this example, we have two identical temperature devices, so we only register the last ID
#define MYDEVICE_1 CUSTOM_DEVICE_START_ID
#define MYDEVICE_2 CUSTOM_DEVICE_START_ID+1
#define LAST_DEVICE_ID MYDEVICE_2
//


//
// Create as many subclasses of deviceDefinition 
// to meet the number of distinct device the node will handle
//

 
class tempMeasureDevice: public deviceDefinition{
  public:
    tempMeasureDevice();
    void getRegisterDescription(int registerNumber, simpleBuffer spb) override;
    void getRegisterValue(int registerNumber, simpleBuffer spb) override;

};


// 
// Subclass the node class to build the custom node
//

class customNodeDefinition: public nodeDefinition{
  public:
    customNodeDefinition();
    void configureCustomNode();
    
    deviceDefinition* getDevice(int deviceNumber) override;
    int getLastDeviceID() override;
        
  protected:
  // Allocate space to store custom device data, here we create space for two temperature Mesure Devices.
    tempMeasureDevice myDevice1;
    tempMeasureDevice myDevice2;
  
};


#endif
