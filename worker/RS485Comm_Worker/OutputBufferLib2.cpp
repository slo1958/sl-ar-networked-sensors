
#include "OutputBufferLib2.h"


outputBufferHandler::outputBufferHandler(genericSerial sr, char * pbuf, int len) : simpleBuffer(pbuf, len){
  _mySerial2 = &sr;
  clearBuffer();
}

void outputBufferHandler::clearBuffer() {
  simpleBuffer::clearBuffer();
  _BufferIndex=0;
}

void outputBufferHandler::addBoolean(bool value) {
  setBooleanAt(value, _BufferIndex);
  _BufferIndex += 1;
  setCharAt(_BufferIndex, 0);

}



void outputBufferHandler::addChar(char cc){
  setCharAt(_BufferIndex, cc);
  _BufferIndex += 1;
  setCharAt(_BufferIndex, 0);
}


void outputBufferHandler::endBuffer(){
  setCharAt(_BufferIndex, ';');
  _BufferIndex += 1;
  setCharAt(_BufferIndex, 0);
}
