
#ifndef deviceAndNode_h
#define deviceAndNode_h

#include "Arduino.h" 
#include <EEPROM.h>
#include "simpleBuffer.h"

#define REGISTER_DATA_TYPE_ERROR '@'

#define REGISTER_DATA_TYPE_BOOLEAN 'A'
#define REGISTER_DATA_TYPE_HEXINT2CHAR 'B'
#define REGISTER_DATA_TYPE_HEXINT4CHAR 'C'
#define REGISTER_DATA_TYPE_SCALEDFLOAT 'D'
#define REGISTER_DATA_TYPE_STR 'E'

#define REGISTER_MODE_ERROR '@'
#define REGISTER_MODE_RO '0'
#define REGISTER_MODE_RW '1'

// Standard registers expected in all devices
#define REGISTER_DEVICE_NAME 0
#define REGISTER_MODEL_ID 1
#define REGISTER_DEVICE_REGISTER_LAST_ID 2
#define REGISTER_DEVICE_BRAND 3
#define REGISTER_DEVICE_ACTIVE 4

#define CUSTOM_REGISTER_START_NUMBER 0x10

// Register in the node info device
#define REGISTER_NODE_INFO_LAST_DEV_ID CUSTOM_REGISTER_START_NUMBER + 0
#define REGISTER_NODE_INFO_ERRORS CUSTOM_REGISTER_START_NUMBER + 1
#define REGISTER_NODE_INFO_LOC_COM CUSTOM_REGISTER_START_NUMBER + 2

#define NODE_INFO_DEVICE_LAST_REGISTER REGISTER_NODE_INFO_LOC_COM

#define NODE_INFO_DEVICE_ID 0

#define CUSTOM_DEVICE_START_ID 1

class nodeDefinition;

// ==== Generic device

class deviceDefinition{
  public:
    deviceDefinition();
    virtual void configureDevice();

//  Utility functions used by all devices
    void storeRegisterDescriptionInBuffer(int registerNumber, char UoM[], char datatype, char mode, char label[], simpleBuffer spb);
    
    void storeRegisterValueInBuffer(int registerNumber, char value[], simpleBuffer spb);
    void loadRegisterValueFromBuffer(int registerNumber, simpleBuffer spb);

    void storeRegisterNoValueInBuffer(int registerNumber, simpleBuffer spb);

    void storeRegisterBoolValueInBuffer(int registerNumber, bool value, simpleBuffer spb);
    void storeRegisterInt2ValueInBuffer(int registerNumber, int value, simpleBuffer spb);
    void loadRegisterInt2ValueFromBuffer(int registerNumber,simpleBuffer spb);

    void storeRegisterInt4ValueInBuffer(int registerNumber, int value, simpleBuffer spb);
    void loadRegisterInt4ValueFromBuffer(int registerNumber,simpleBuffer spb);

    void storeRegisterScaledFloatValueInBuffer(int registerNumber, long value, simpleBuffer spb);
    
// Device specific functions, that must be overloaded in the definition of the custom device(s)
    virtual void getRegisterDescription(int registerNumber, simpleBuffer spb);

    virtual void getRegisterValue(int registerNumber, simpleBuffer spb);
    virtual void setRegisterValue(int registerNumber, simpleBuffer spb);
 
 protected:
    int _DeviceAddr;
    int _FlashLedMode;
};

// ==== Node information device

class nodeInfoDeviceDefinition: public deviceDefinition {
  public:
    nodeInfoDeviceDefinition();
    void setLastError(int lastError);
    
    void configureDevice() override;
    void getRegisterDescription(int registerNumber, simpleBuffer spb) override;
    
    void getRegisterValue(int registerNumber, simpleBuffer spb) override;
    void setRegisterValue(int registerNumber, simpleBuffer spb) override;

    nodeDefinition* myNode;
    
  protected:
    int _lastError;

};


// ==== Node

class nodeDefinition{
  public:
    nodeDefinition();
    void configureCommonNode();
    
    bool validNodeAddress(int addr);
    void setNodeAddress(int addr);
    int getNodeAddr();
    int getLastDeviceID();
    
    void setFlashLedMode(bool mode);
    bool getFlashLedMode();

    virtual deviceDefinition* getDevice(int deviceNumber);
    
    void getRegisterDescription(int deviceNumber, int registerNumber, simpleBuffer spb);
    
    void getRegisterValue(int deviceNumber, int registerNumber, simpleBuffer spb);
    void setRegisterValue(int deviceNumber, int registerNumber, simpleBuffer spb);  

    //int lastDeviceID = 1;
    char nodeName[16] = "TestNode";
    char nodeModel[16] = "Dummy";
    char nodeBrand[16] = "SLO";
    
 protected:
    int _NodeAddr;
    int _FlashLedMode;
    nodeInfoDeviceDefinition _baseDevice;
    int _lastDeviceID = 1;
};

 
#endif
