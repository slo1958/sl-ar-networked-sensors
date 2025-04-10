
#include "SerialComm.h"

genericSerial::genericSerial(){
  _readWriteControlPin = -1;
}
    
bool genericSerial::byteAvailable(){
  return false;
}

char genericSerial::byteRead(){
  ;
}

void genericSerial::xbegin(int xferSpeed){
  ;
}

void genericSerial::flush(){
  ;
}

void genericSerial::setReadWriteControl(int controlPin,   byte readMode, byte writeMode){
    _readWriteControlPin = controlPin;
    _readMode = readMode;
    _writeMode = writeMode;

    pinMode(_readWriteControlPin, OUTPUT);
    doneWriting();
}

void genericSerial::startWriting(){
  if (_readWriteControlPin < 1) return;
  digitalWrite(_readWriteControlPin, _writeMode);
  delay(5);
}

void genericSerial::doneWriting(){
  flush();
  if (_readWriteControlPin < 1) return;
  delay(5);
  digitalWrite(_readWriteControlPin, _readMode);
}

hardwareSerial::hardwareSerial(){
  ;
}

bool hardwareSerial::byteAvailable() {
  return Serial.available();
}
    
char hardwareSerial::byteRead() {
  return Serial.read();
}
    
void hardwareSerial::xbegin(int xferSpeed) {
  Serial.begin(xferSpeed);
}

void hardwareSerial::flush(){
  Serial.flush();
}

softwareSerial::softwareSerial(int rx_pin, int tx_pin){
  _mySerial = &SoftwareSerial(rx_pin, tx_pin, false); 
}

bool softwareSerial::byteAvailable() {
  return _mySerial->available();
}
    
char softwareSerial::byteRead() {
  return _mySerial->read();
}

void softwareSerial::xbegin(int xferSpeed) {
   _mySerial->begin(xferSpeed);
}


void softwareSerial::flush(){
  _mySerial->flush();

}
