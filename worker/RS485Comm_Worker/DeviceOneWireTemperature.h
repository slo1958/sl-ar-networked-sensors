#ifndef DeviceOneWireTemperature_h
#define DeviceOneWireTemperature_h


#include "Arduino.h" 
#include "DeviceAndNode.h"

#include <DallasTemperature.h>

class OneWireTemperatureDevice: public deviceDefinition{
  public:
    OneWireTemperatureDevice();
    void getRegisterDescription(int registerNumber, simpleBuffer spb) override;
    void getRegisterValue(int registerNumber, simpleBuffer spb) override;

    float getTemperature();
    
    DallasTemperature sensors;
    int sensorID;
    
};

#endif
