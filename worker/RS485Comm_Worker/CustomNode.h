#ifndef customNode_h
#define customNode_h


#include "Arduino.h" 
#include "DeviceAndNode.h"

//
// Devices are using the OneWire bus
// Data wire is connected to GPIO 4
#define ONE_WIRE_BUS_IO 4

#include <OneWire.h>



// We have Dallas temperature probes on 1-Wire
#include <DallasTemperature.h>

//
// Add the definition of the devices used in the node
//
#include "DeviceOneWireTemperature.h"


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
// Subclass the node class to build the custom node
//

class customNodeDefinition: public nodeDefinition{
  public:
    customNodeDefinition();
    void configureCustomNode();
    
    deviceDefinition* getDevice(int deviceNumber) override;

    bool SensorParasitePower;
    bool SensorDeviceFound;
    int SensorCount = 0;
    
  protected:
  // Allocate space to store custom device data, here we create space for two temperature Mesure Devices.
    OneWireTemperatureDevice myDevice1;
    OneWireTemperatureDevice myDevice2;
  
};


#endif
