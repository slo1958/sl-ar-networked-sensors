
#ifndef inputBufferHandler_h
#define inputBufferHandler_h

#include "Arduino.h" 
#include <SoftwareSerial.h>
#include "SerialComm.h"
#include "simpleBuffer.h"
 

class inputBufferHandler: public simpleBuffer{

  public:
    inputBufferHandler(genericSerial sr, char * pbuf, int len);
    bool inputCommandReady();
    long inputBufferAge();
    void clearBuffer() override;
    void checkAnyMessage();
    void clearOldData(long maxAge);
  
        
    virtual bool byteAvailable();
    virtual char byteRead();
    
  private:
    genericSerial * _mySerial2;
    bool _BufferLocked;
    int _BufferIndex;
    unsigned long _lastInputBufferReset;
    
};
 

#endif
