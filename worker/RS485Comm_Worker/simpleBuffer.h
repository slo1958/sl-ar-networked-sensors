#ifndef simpleBuffer_h
#define simpleBuffer_h

#include "Arduino.h" 

#define BUFFER_SIZE 32


class simpleBuffer{
  public:
    simpleBuffer(char * p, int len);
        
    void moveChars(int offset, const char source[], int maxlen);
    void moveBytes(int offset, char source[], int movelen);

    void replaceChar(char findChar, char replChar);
    
    virtual void clearBuffer();
    
    bool anyData();
    
    char getCharAt(int offset);
    int getDigitAt(int offset);
    int getHexDigitAt(int offset);
    long getHexDigitsAt(int offset, int limit);
    int getHexByteAt(int offset);
 
    void setCharAt(int offset, char c);
    void setDigitAt(int offset, int v);
    void setHexDigitsAt(int offset, long v, int limit);
    void setHexDigitAt(int offset, int v);
    void setHexByteAt(int offset, int v);   
    void setSignedHexDigitsAt(int offset, long v, int limit);

    void resetBaseOffset();
    void setBaseOffset(int offset);
    
  protected:
    char * _buf;
    int _len;
    int _baseOffset;
};



#endif
