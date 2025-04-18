
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
    
  private:
    genericSerial * _mySerial2;
    char _inputBuffer[INPUT_BUFFER_SIZE];
    int _inputBufferIndex;
    bool _inputBufferLocked;
    unsigned long _lastInputBufferReset;
    
};
 

#endif
