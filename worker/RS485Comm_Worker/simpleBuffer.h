#ifndef simpleBuffer_h
#define simpleBuffer_h

#include "Arduino.h" 

#define BUFFER_SIZE 32


class simpleBuffer{
  public:
    simpleBuffer(char * p, int len);
    void moveChars(const char source[], int destpos);
    void moveBytes(char source[], int movelen, int destpos);
    virtual void clearBuffer();
    bool anyData();
    
    char getCharAt(int offset);
    int getDigitAt(int offset);
    int getHexDigitAt(int offset);
    int getHexByteAt(int offset);
    int getHexWordAt(int offset);
    long getHexLongAt(int offset);
     
    void setCharAt(int offset, char c);
    void setDigitAt(int offset, int v);
    void setHexDigitAt(int offset, int v);
    void setHexByteAt(int offset, int v);   
    void setHexWordAt(int offset, int v);   
    void setHexLongAt(int offset, long v);
       
  protected:
    char * _buf;
    int _len;
};



#endif
