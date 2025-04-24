
#include "OutputBufferLib2.h"


outputBufferHandler::outputBufferHandler(genericSerial p){
  _mySerial2 = &p;
  clearBuffer();
}

void outputBufferHandler::clearBuffer() {
  commonBufferHandler::clearBuffer();
}

void outputBufferHandler::addBoolean(bool value) {
  setBooleanAt(value, _BufferIndex);
  _BufferIndex += 1;
}

void outputBufferHandler::setBooleanAt(bool value, int index){
   _Buffer[index] = (value ? '1' : '0');
   _Buffer[index+1] = 0; 
}
