
#ifndef outputBufferHandler_h
#define outputBufferHandler_h

#include "Arduino.h" 
#include <SoftwareSerial.h>
#include "SerialComm.h"
#include "simpleBuffer.h"

class outputBufferHandler: public simpleBuffer{

  public:
    outputBufferHandler(genericSerial sr, char * pbuf, int len);
    void clearBuffer() override;
    void addBoolean(bool value);
    void setBooleanAt(bool value, int index);
 

    void addChar(char cc);
    
    void endBuffer();
    
  private:
    genericSerial * _mySerial2;
    int  _BufferIndex;
};

#endif
