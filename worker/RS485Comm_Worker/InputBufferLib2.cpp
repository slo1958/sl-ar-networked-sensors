
#include "InputBufferLib2.h"

inputBufferHandler::inputBufferHandler(){
  clearInputBuffer();
}

bool inputBufferHandler::anyDataInBuffer(){
    return _inputBufferIndex > 0; 
}

bool inputBufferHandler::inputCommandReady(){
  return _inputBufferLocked; 
}

long inputBufferHandler::inputBufferAge(){
    return millis() - _lastInputBufferReset;
}

char inputBufferHandler::getCharAt(int charIndex){
  return _inputBuffer[charIndex];
}
    
void inputBufferHandler::clearInputBuffer(){
  for (int i = 0; i < INPUT_BUFFER_SIZE; i++) _inputBuffer[i] = 0;
  _inputBufferLocked = false;
  _inputBufferIndex = 0;
  _lastInputBufferReset = millis();
}

void inputBufferHandler::clearOldData(long maxAge){
  if (inputBufferAge() > maxAge) clearInputBuffer();
}

void inputBufferHandler::checkAnyMessage() {
    if (_inputBufferLocked) return;

  while (byteAvailable() > 0) {
    char x = byteRead();
    if (!isControl(x)) {
      _inputBuffer[_inputBufferIndex] = x;
      _inputBufferLocked = (x == ';');
      
      if (x == '*') {
        clearInputBuffer();
        _inputBufferLocked = false;
      } else if (_inputBufferIndex < INPUT_BUFFER_SIZE) _inputBufferIndex += 1;              

     
     _lastInputBufferReset = millis();
     }    
  }
}

bool inputBufferHandler::byteAvailable(){
  return false;
}

char inputBufferHandler::byteRead(){
  return 0;
}

void inputBufferHandler::xbegin(int xferSpeed){
  ;
}


inputBufferHardSerial::inputBufferHardSerial(int dummy){
   clearInputBuffer();
}

bool inputBufferHardSerial::byteAvailable() {
  return Serial.available();
}

char inputBufferHardSerial::byteRead() {
  return Serial.read();
}

void inputBufferHardSerial::xbegin(int xferSpeed){
  Serial.begin(xferSpeed);
}


inputBufferSoftSerial::inputBufferSoftSerial(int rx_pin, int tx_pin) {
  _mySerial = &SoftwareSerial(rx_pin, tx_pin, false); 
  clearInputBuffer();
}

bool inputBufferSoftSerial::byteAvailable() {
  return _mySerial->available();
}

char inputBufferSoftSerial::byteRead() {
  return _mySerial->read();
}


void inputBufferSoftSerial::xbegin(int xferSpeed){
   _mySerial->begin(xferSpeed);
}
