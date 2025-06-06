
#ifndef inputBufferHandler_h
#define inputBufferHandler_h

#include "Arduino.h" 
#include <SoftwareSerial.h>
#include "SerialComm.h"
#include "CommonBufferLib2.h"

class inputBufferHandler: public commonBufferHandler{

  public:
    inputBufferHandler(genericSerial p);
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
    unsigned long _lastInputBufferReset;
    
};
 

#endif
