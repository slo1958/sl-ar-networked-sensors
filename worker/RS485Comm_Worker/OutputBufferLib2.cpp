
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
  _Buffer[_BufferIndex] = 0; 

}



void outputBufferHandler::addChar(char cc){
  _Buffer[_BufferIndex] = cc;
  _BufferIndex += 1;
  _Buffer[_BufferIndex] = 0;
}


void outputBufferHandler::endBuffer(){
  _Buffer[_BufferIndex] = ';';
  _BufferIndex += 1;
  _Buffer[_BufferIndex] = 0;
}
