
#include "InputBufferLib2.h"

inputBufferHandler::inputBufferHandler(genericSerial sr, char * pbuf, int len) : simpleBuffer(pbuf, len){
  _mySerial2 = &sr;
  clearBuffer();
}

bool inputBufferHandler::inputCommandReady(){
  return _BufferLocked; 
}

long inputBufferHandler::inputBufferAge(){
    return millis() - _lastInputBufferReset;
}


    
void inputBufferHandler::clearBuffer(){
  simpleBuffer::clearBuffer();
  _BufferIndex = 0;
  _BufferLocked = false;
  _lastInputBufferReset = millis();
}

void inputBufferHandler::clearOldData(long maxAge){
  if (inputBufferAge() > maxAge) clearBuffer();
}

void inputBufferHandler::checkAnyMessage() {
    if (_BufferLocked) return;

  while (byteAvailable() > 0) {
    char x = byteRead();
    if (!isControl(x)) {
      setCharAt(_BufferIndex,x);
      _BufferLocked = (x == ';');
      
      if (x == '*') {
        clearBuffer();
        _BufferLocked = false;
      } else if (_BufferIndex < _len) _BufferIndex += 1;              

     
     _lastInputBufferReset = millis();
     }    
  }
}


bool inputBufferHandler::byteAvailable(){
  return _mySerial2->byteAvailable();
}

char inputBufferHandler::byteRead(){
  return _mySerial2->byteRead();
}




 
