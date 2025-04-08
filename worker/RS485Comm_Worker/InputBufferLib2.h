
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
    void clearOldData(long maxAge);
    char getCharAt(int charIndex);
    virtual bool byteAvailable();
    virtual char byteRead();
    virtual void xbegin(int xferSpeed);
    
  private:
    char _inputBuffer[INPUT_BUFFER_SIZE];
    int _inputBufferIndex;
    bool _inputBufferLocked;
    unsigned long _lastInputBufferReset;
    
};

class inputBufferHardSerial:public inputBufferHandler {
  public:
    inputBufferHardSerial(int dummy);
    
    bool byteAvailable() override;
    char byteRead() override;
    void xbegin(int xferSpeed) override;
};

class inputBufferSoftSerial:public inputBufferHandler {
  public:
    inputBufferSoftSerial(int rx_pin, int tx_pin);
  
    bool byteAvailable() override;
    char byteRead() override;
    void xbegin(int xferSpeed) override;
    
  private:
    SoftwareSerial * _mySerial;
};

#endif
