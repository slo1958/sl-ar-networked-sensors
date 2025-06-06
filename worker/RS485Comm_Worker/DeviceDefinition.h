
#ifndef deviceDefinition_h
#define deviceDefinition_h

 

class deviceDefinition{
  public:
    deviceDefinition();
    virtual void configureDevice();
    virtual void getDeviceModelID(char v[], int bufferLength);    
    virtual void getDeviceName(char v[], int bufferLength);
    virtual int getDeviceRegisterCount();
    virtual void getSpecificRegisterDescription(int registerNumber, char v[], int bufferLength);

    void getRegisterDescription(int registerNumber, char v[], int bufferLength);

    virtual void getSpecificDeviceRegisterValue(int registerNumber);

    void getDeviceRegisterValue(int registerNumber);
    
    virtual void settDeviceRegisterValue(int registerNumber);


 
 protected:
    int _DeviceAddr;
    int _FlashLedMode;
};

#endif
