
#ifndef outputBufferHandler_h
#define outputBufferHandler_h

#include "Arduino.h" 
#include <SoftwareSerial.h>
#include "SerialComm.h"
#include "CommonBufferLib2.h"

class outputBufferHandler: public commonBufferHandler{

  public:
    outputBufferHandler(genericSerial p);
    void clearBuffer() override;
    void addBoolean(bool value);
    void setBooleanAt(bool value, int index);
 

    void addChar(char cc);
    
    void endBuffer();
    
  private:
    genericSerial * _mySerial2;
};

#endif
