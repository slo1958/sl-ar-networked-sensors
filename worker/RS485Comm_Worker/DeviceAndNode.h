
#ifndef deviceAndNode_h
#define deviceAndNode_h

#include "Arduino.h" 
#include <EEPROM.h>

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

// ==== Device

class deviceDefinition{
  public:
    deviceDefinition();
    virtual void configureDevice();
    
    void getModelID(char v[], int bufferLength);    
    void getName(char v[], int bufferLength);
    int getRegisterLastID();

    void descriptionSetRegsiterNumber(int registerNumber, char v[]);
    void descriptionSetUoM(char UoM[], char v[]);
    void descriptionSetRWMode(char mode, char v[]);
    void descriptionSetLabel(char label[], char v[]);
    
    virtual void getRegisterDescription(int registerNumber, char v[], int bufferLength);

    virtual void getRegisterValue(int registerNumber, char v[], int bufferLength);
    virtual void setRegisterValue(int registerNumber, char v[], int bufferLength);


    virtual int getRegisterIntegerValue(int registerNumber);
    virtual int setRegisterIntegerValue(int registerNumber);
 
 protected:
    int _DeviceAddr;
    int _FlashLedMode;
};


class nodeInfoDeviceDefinition: public deviceDefinition {
  public:
    nodeInfoDeviceDefinition();
    void configureDevice() override;
    int getRegisterIntegerValue(int registerNumber) override;
    void getRegisterDescription(int registerNumber, char v[], int bufferLength) override;
    void setLastDeviceID(int lastDeviceID);
    void setLastError(int lastError);
    
  protected:
    int _lastDeviceID;
    int _lastError;

};


// ==== NODE
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
    
    void getRegisterDescription(int deviceNumber, int registerNumber, char v[], int bufferLength);
    void getRegisterValue(int deviceNumber, int registerNumber);
    void setRegisterValue(int deviceNumber, int registerNumber);  

 protected:
    int _NodeAddr;
    int _FlashLedMode;
    nodeInfoDeviceDefinition _baseDevice;
};


#endif
