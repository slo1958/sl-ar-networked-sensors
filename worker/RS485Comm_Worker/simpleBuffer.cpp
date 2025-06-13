
#include "simpleBuffer.h"


simpleBuffer::simpleBuffer(char * p, int len) {
  _buf = p;
  _len = len;
}


void simpleBuffer::moveChars(const char source[], int destpos){
  int i;
  for (i=0;source[i] != 0; i++) _buf[destpos+i] = source[i];
  _buf[destpos+i] = 0;    
}


void simpleBuffer::moveBytes(char source[], int movelen, int destpos){
  int i;
    for (i=0;i < movelen; i++) _buf[destpos+i] = source[i];
    _buf[destpos+i] = 0;     
}

void simpleBuffer::clearBuffer(){
  int i;
    for (i=0;i < _len; i++) _buf[i] = 0;
}

bool simpleBuffer::anyData(){
   int i;
    for (i=0;i < _len; i++)  if (_buf[i] != 0) return true;
    return false;
}

char simpleBuffer::getCharAt(int offset){
    if (offset < _len) return _buf[offset];
    return '!';
}


int simpleBuffer::getDigitAt(int offset) {
  char x;
  if (offset >= _len ) return -1;
  x = _buf[offset];
  if (isdigit(x)) return x - '0';
  return -1;
}

int simpleBuffer::getHexDigitAt(int offset) {
  char x;
  if (offset >= _len ) return -1;
  x = _buf[offset];
  if (isdigit(x)) return x - '0';
  if (( 'A' <= x ) && (x <= 'F')) return x - 'A'+ 10;
  return -1;
}

int simpleBuffer::getHexByteAt(int offset) {
  int v1 = getHexDigitAt(offset);
  int v2 = getHexDigitAt(offset+1);
  if (v1 >= 0 && v2 >=0 ) return v1*16+v2;
  return -1;
}

int simpleBuffer::getHexWordAt(int offset){
  int v1 = getHexByteAt(offset);
  int v2 = getHexByteAt(offset+2);
  if (v1 >= 0 && v2 >=0 ) return v1*256+v2;
  return -1;
}

long simpleBuffer::getHexLongAt(int offset){
  long v1 = getHexWordAt(offset);
  long v2 = getHexWordAt(offset+4);
  if (v1 >= 0 && v2 >=0 ) return v1*65536+v2;
  return -1;
}

void simpleBuffer::setCharAt(int offset, char c){
    if (offset < _len)  _buf[offset] = c;
}

void simpleBuffer::setDigitAt(int offset, int v){
  if (v<0) return;
  if (v>9) return;
  setCharAt(offset, (v + '0'));
}

void simpleBuffer::setHexDigitAt(int offset, int v){
  if (v<0) return;
  if (v>15) return;
  setCharAt(offset, (v < 10 ? v + '0' : v - 10 + 'A'));
}


void simpleBuffer::setHexByteAt(int offset, int v) {
    int8_t c = v % 16;
    setCharAt(offset+1, (c < 10 ? c + '0' : c - 10 + 'A'));
    
    c = v / 16;
    setCharAt(offset, (c < 10 ? c + '0' : c - 10 + 'A'));
}


void simpleBuffer::setHexWordAt(int offset, int v){
   uint16_t c = v % 256;
   setHexByteAt(offset+2, c);
   
   c = v / 256;
   setHexByteAt(offset, c);
   
}

void simpleBuffer::setHexLongAt(int offset, long v){
    uint32_t c = v % 65536;
    setHexWordAt(offset+4, c);
    
    c = v / 65536;
    setHexWordAt(offset, c);

}
