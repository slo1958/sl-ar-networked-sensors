
#include "InputBufferLib2.h"

inputBufferHandler::inputBufferHandler(genericSerial p){
  _mySerial2 = &p;
  clearBuffer();
}

bool inputBufferHandler::inputCommandReady(){
  return _BufferLocked; 
}

long inputBufferHandler::inputBufferAge(){
    return millis() - _lastInputBufferReset;
}


    
void inputBufferHandler::clearBuffer(){
  commonBufferHandler::clearBuffer();
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
      _Buffer[_BufferIndex] = x;
      _BufferLocked = (x == ';');
      
      if (x == '*') {
        clearBuffer();
        _BufferLocked = false;
      } else if (_BufferIndex < BUFFER_SIZE) _BufferIndex += 1;              

     
     _lastInputBufferReset = millis();
     }    
  }
}



int inputBufferHandler::extractCheckedAddress(int startbyte) {
  int k1 = getBufferIntAt(startbyte, 3, false);
  if (k1 < 0) return -1;

  int k2 = getBufferIntAt(startbyte + 3, 3, true);
  if (k2 < 0) return -1;

  if (k1 != k2) return -1;
  return k1;
}


bool inputBufferHandler::byteAvailable(){
  return _mySerial2->byteAvailable();
}

char inputBufferHandler::byteRead(){
  return _mySerial2->byteRead();
}




 
