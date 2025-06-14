
#ifndef deviceAndNode_h
#define deviceAndNode_h

#include "Arduino.h" 
#include <EEPROM.h>
#include "simpleBuffer.h"

#define REGISTER_DATA_TYPE_ERROR '@'

#define REGISTER_DATA_TYPE_RO_BOOLEAN 'A'
#define REGISTER_DATA_TYPE_RO_HEXINT2CHAR 'B'
#define REGISTER_DATA_TYPE_RO_HEXINT4CHAR 'C'
#define REGISTER_DATA_TYPE_RO_FLOAT 'D'
#define REGISTER_DATA_TYPE_RO_STR 'E'
 
#define REGISTER_DATA_TYPE_RW_BOOLEAN 'N'
#define REGISTER_DATA_TYPE_RW_HEXINT2CHAR 'P'
#define REGISTER_DATA_TYPE_RW_HEXINT4CHAR  'Q'
#define REGISTER_DATA_TYPE_RW_FLOAT 'R'
#define REGISTER_DATA_TYPE_RW_STR 'S'

#define REGISTER_DEVICE_NAME 0
#define REGISTER_MODEL_ID 1
#define REGISTER_DEVICE_REGISTER_LAST_ID 2
#define REGISTER_DEVICE_BRAND 3

#define REGISTER_START_NUMBER 0x10

#define REGISTER_NODE_INFO_LAST_DEV_ID 0x10
#define REGISTER_NODE_INFO_ERRORS 0x11
#define REGISTER_NODE_INFO_LOC_COM 0x12

#define NODE_DEVICE_ID 0


// ==== Generic device

class deviceDefinition{
  public:
    deviceDefinition();
    virtual void configureDevice();
    
    void getModelID(simpleBuffer spb);    
    void getName(simpleBuffer spb);
    int getRegisterLastID();

    void setRegisterDescription(int registerNumber, char UoM[], char mode, char label[], simpleBuffer spb);
    
    virtual void getRegisterDescription(int registerNumber, simpleBuffer spb);

    virtual void getRegisterValue(int registerNumber, simpleBuffer spb);
    virtual void setRegisterValue(int registerNumber, simpleBuffer spb);

    virtual int getRegisterIntegerValue(int registerNumber);
    virtual int setRegisterIntegerValue(int registerNumber);
 
 protected:
    int _DeviceAddr;
    int _FlashLedMode;
};

// ==== Node information device

class nodeInfoDeviceDefinition: public deviceDefinition {
  public:
    nodeInfoDeviceDefinition();
    void configureDevice() override;
    int getRegisterIntegerValue(int registerNumber) override;
    void getRegisterDescription(int registerNumber, simpleBuffer spb) override;
    void setLastDeviceID(int lastDeviceID);
    void setLastError(int lastError);
    
  protected:
    int _lastDeviceID;
    int _lastError;

};


// ==== Node

class nodeDefinition{
  public:
    nodeDefinition();
    void configureNode();
    void configureDevices();
    void startDevices();
    
    bool validNodeAddress(int addr);
    void setNodeAddress(int addr);
    int getNodeAddr();
    void setFlashLedMode(bool mode);
    bool getFlashLedMode();

    virtual int getLastDeviceID();
    virtual deviceDefinition* getDevice(int deviceNumber);
    
    void getRegisterDescription(int deviceNumber, int registerNumber, simpleBuffer spb);
    void getRegisterValue(int deviceNumber, int registerNumber);
    void setRegisterValue(int deviceNumber, int registerNumber);  

 protected:
    int _NodeAddr;
    int _FlashLedMode;
    nodeInfoDeviceDefinition _baseDevice;
};


#endif
