
#ifndef inputBufferHandler_h
#define inputBufferHandler_h

#include "Arduino.h" 
#include <SoftwareSerial.h>
#include "SerialComm.h"

#define INPUT_BUFFER_SIZE 32

class inputBufferHandler{

  public:
    inputBufferHandler(genericSerial p);
    bool anyDataInBuffer();
    bool inputCommandReady();
    long inputBufferAge();
    void clearInputBuffer();
    void checkAnyMessage();
    void clearOldData(long maxAge);
    char getCharAt(int charIndex);
    int getBufferFlagAt(int offset);
    int getBufferIntAt(int offset, int count, bool inverted);
    int extractCheckedAddress(int startbyte);
    
    virtual bool byteAvailable();
    virtual char byteRead();
    virtual void xbegin(int xferSpeed);
    
  private:
    genericSerial * _mySerial2;
    char _inputBuffer[INPUT_BUFFER_SIZE];
    int _inputBufferIndex;
    bool _inputBufferLocked;
    unsigned long _lastInputBufferReset;
    
};

class inputBufferHardSerial:public inputBufferHandler {
  public:
    inputBufferHardSerial();
    
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
