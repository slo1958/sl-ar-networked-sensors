
#ifndef tempMeasureNode_h
#define tempMeasureNode_h

#include "Arduino.h" 

#include "DeviceAndNode.h"
 

class tempMeasureDevice: public deviceDefinition{
  public:
    tempMeasureDevice();
    void getRegisterDescription(int registerNumber, simpleBuffer spb) override;
    int getRegisterIntegerValue(int registerNumber) override;
  
};

class tempMeasureNode: public nodeDefinition{
  public:
    tempMeasureNode();
    deviceDefinition* getDevice(int deviceNumber) override;
    int getLastDeviceID() override;
        
  protected:
    tempMeasureDevice myDevice[2];
  
};

#endif
