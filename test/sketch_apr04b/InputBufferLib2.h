
#ifndef inputBufferHandler_h
#define inputBufferHandler_h

#include "Arduino.h" 
#include <SoftwareSerial.h>

#define INPUT_BUFFER_SIZE 32

class inputBufferHandler{

  public:
    inputBufferHandler();
    bool anyDataInBuffer();
    bool inputCommandReady();
    long inputBufferAge();
    void clearInputBuffer();
    void checkAnyMessage();

    virtual bool byteAvailable();
    virtual char byteRead();
    
  private:
    char _inputBuffer[INPUT_BUFFER_SIZE];
    int _inputBufferIndex;
    bool _inputBufferLocked;
    unsigned long _lastInputBufferReset;
    
};

class inputBufferHardSerial:inputBufferHandler {
    bool byteAvailable() override;
    char byteRead() override;
};

class inputBufferSoftSerial:inputBufferHandler {
  public:
    inputBufferSoftSerial(int rx_pin, int tx_pin);
  
    bool byteAvailable() override;
    char byteRead() override;
    
  private:
    SoftwareSerial * _mySerial;
};

#endif
