
#include "CommonBufferLib2.h"


commonBufferHandler::commonBufferHandler(){
  clearBuffer();
}

void commonBufferHandler::clearBuffer(){
  for (int i = 0; i < BUFFER_SIZE; i++) _Buffer[i] = 0;
  _BufferIndex = 0;
}


bool commonBufferHandler::anyDataInBuffer(){
    return _BufferIndex > 0; 
}


char commonBufferHandler::getCharAt(int charIndex){
  return _Buffer[charIndex];
}

int commonBufferHandler::getBufferFlagAt(int offset) {
  char x;
  if (offset > BUFFER_SIZE) return -1;
  if (offset > _BufferIndex) return -1;
  x = _Buffer[offset];
  if (isdigit(x)) return x - '0';
  return -1;
}


int commonBufferHandler::getBufferIntAt(int offset, int count, bool inverted) {
  int k1 = 0;
  for (int i = offset; i < offset + count; i++) {
    if (i <= _BufferIndex) {
      char x = _Buffer[i];
      if (isDigit(x)) {
        k1 = k1 * 10 + (inverted ? (9 - (x - '0')) :  (x - '0'));
      } else return -1;
    } else return -1;
  }
  return k1;
}
