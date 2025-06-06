
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


int commonBufferHandler::exchangeBetweenBuffers(char inbuffer[], char outBuffer[], int startInPosition, int startOutPosition) {
   int i;
   for (i=startInPosition; inbuffer[i] != 0; i++) outBuffer[startOutPosition+i] = inbuffer[i];
   outBuffer[startOutPosition+i] = 0;
   return startOutPosition + i; 
}

bool commonBufferHandler::getBooleanAt(int offset){
   return (_Buffer[offset] != '0');
}

char commonBufferHandler::getCharAt(int charIndex){
  return _Buffer[charIndex];
}

int commonBufferHandler::getDigitAt(int offset) {
  char x;
  if (offset > BUFFER_SIZE) return -1;
  if (offset > _BufferIndex) return -1;
  x = _Buffer[offset];
  if (isdigit(x)) return x - '0';
  return -1;
}

int commonBufferHandler::getHexDigitAt(int offset) {
  char x;
  if (offset > BUFFER_SIZE) return -1;
  if (offset > _BufferIndex) return -1;
  x = _Buffer[offset];
  if (isdigit(x)) return x - '0';
  if (( 'A' <= x ) && (x <= 'F')) return x - 'A'+ 10;
  return -1;
}

int commonBufferHandler::getHexByteAt(int offset){
  int v1 = getHexDigitAt(offset);
  int v2 = getHexDigitAt(offset+1);
  return v1*16+v2;
    
}

int commonBufferHandler::getUnsignedIntAt(int offset, int count, bool inverted) {
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


long commonBufferHandler::getUnsignedLongAt(int offset, int count, bool inverted) {
  long k1 = 0;
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


int commonBufferHandler::getFromBuffer(int offset, char outBuffer[]){
 return exchangeBetweenBuffers(_Buffer, outBuffer,  offset, 0);
}



void commonBufferHandler::setBooleanAt(int offset,bool v){
   _Buffer[offset] = (v ? '1' : '0');
}

void commonBufferHandler::setCharAt(int offset, char cc) {
  _Buffer[offset] = cc;
}

void commonBufferHandler::setDigitAt(int offset, int v){
  if (v<0) return;
  if (v>9) return;
  _Buffer[offset] = v + '0'; 
}

void commonBufferHandler::setHexDigitAt(int offset, int v){
  if (v<0) return;
  if (v>15) return;
  _Buffer[offset] = (v < 10 ? v + '0' : v - 10 + 'A');
}


void commonBufferHandler::setHexByteAt(int offset, byte v) {
    byte c = v % 16;
    _Buffer[offset+1] = (c < 10 ? c + '0' : c - 10 + 'A');
    c = v / 16;
    _Buffer[offset] = (c < 10 ? c + '0' : c - 10 + 'A');
}

void commonBufferHandler::setHexBytesAt(int offset, byte value[], int vsize){
  int j = offset;

  for (int i=0; i<vsize; i++) {
    unsigned int n = value[i];
 
    byte c = n % 16;
    _Buffer[j+1] = (c < 10 ? c + '0' : c - 10 + 'A');
    c = n / 16;
    _Buffer[j] = (c < 10 ? c + '0' : c - 10 + 'A');
    j += 2;
    
    }
}
 


int commonBufferHandler::putToBuffer(int offset, char inBuffer[]){
 return exchangeBetweenBuffers(inBuffer, _Buffer, 0, offset);
}
 
