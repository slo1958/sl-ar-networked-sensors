#ifndef commonBufferHandler_h
#define commonBufferHandler_h

#include "Arduino.h" 

#define BUFFER_SIZE 32

class commonBufferHandler{

  public:
    commonBufferHandler();
    virtual void clearBuffer();
    bool anyDataInBuffer();

    int exchangeBetweenBuffers(char inbuffer[], char outBuffer[], int startInPosition, int startOutPosition);

    bool getBooleanAt(int offset);
    char getCharAt(int charIndex);
    int getDigitAt(int offset);
    int getHexDigitAt(int offset);
    int getHexByteAt(int offset);
    int getUnsignedIntAt(int offset, int count, bool inverted);
    long getUnsignedLongAt(int offset, int count, bool inverted);

    int getFromBuffer(int offset, char outBuffer[]);
    
    void setBooleanAt(int offset,bool v);
    void setCharAt(int offset, char cc);
    void setDigitAt(int offset, int v);
    void setHexDigitAt(int offset, int v);

    void setHexByteAt(int offset, byte v);

    
    void setHexBytesAt(int offset, byte value[], int vsize);


    int putToBuffer(int offset, char inBuffer[]);
    
//    int putConvertedToBuffer(int offset);
    
//    char conversionBuffer[20];
    
  protected:
    char _Buffer[BUFFER_SIZE];
    int _BufferIndex;
};

#endif
