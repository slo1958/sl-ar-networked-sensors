
#ifndef serialcomm_h
#define serialcomm_h

#include "Arduino.h" 
#include <SoftwareSerial.h>

class genericSerial{
  public:
    genericSerial();
    void setReadWriteControl(int controlPin, byte readMode, byte writeMode);
    void startWriting();
    void doneWriting();
    virtual bool byteAvailable();
    virtual char byteRead();
    virtual void xbegin(int xferSpeed);
    virtual void flush();

  private:
    byte _readWriteControlPin;
    byte _readMode;
    byte _writeMode;
    
};

class hardwareSerial: public genericSerial {
  public:
    hardwareSerial();

    bool byteAvailable() override;
    char byteRead() override;
    void xbegin(int xferSpeed) override;
    void flush() override;
};


class softwareSerial: public genericSerial {
  public:
    softwareSerial(int rx_pin, int tx_pin);

    bool byteAvailable() override;
    char byteRead() override;
    void xbegin(int xferSpeed) override;
    void flush() override;
      
  private:
    SoftwareSerial * _mySerial;
    
};

#endif
