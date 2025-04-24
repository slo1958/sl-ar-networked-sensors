#ifndef commonBufferHandler_h
#define commonBufferHandler_h

#include "Arduino.h" 

#define BUFFER_SIZE 32

class commonBufferHandler{

  public:
    commonBufferHandler();
    virtual void clearBuffer();
    bool anyDataInBuffer();
    char getCharAt(int charIndex);
    int getBufferFlagAt(int offset);
    int getBufferIntAt(int offset, int count, bool inverted);

    
  protected:
    char _Buffer[BUFFER_SIZE];
    int _BufferIndex;
};

#endif
