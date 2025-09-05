
#include "simpleBuffer.h"


simpleBuffer::simpleBuffer(char * p, int len) {
  _buf = p;
  _len = len;
  _baseOffset = 0;
}

//
//void simpleBuffer::moveChars(const char source[], int destpos){
//  int i;
//  for (i=0;source[i] != 0; i++) _buf[destpos+i] = source[i];
//  _buf[destpos+i] = 0;    
//}

void simpleBuffer::moveChars(int offset, const char source[], int maxlen){
  int i;
  for (i=0;(source[i] != 0 && i<maxlen); i++) _buf[_baseOffset+offset+i] = source[i];
  _buf[_baseOffset+offset+i] = 0;  
}

//void simpleBuffer::moveBytes(int offset, char source[], int movelen){
//  int i;
//    for (i=0;i < movelen; i++) _buf[_baseOffset+offset+i] = source[i]; 
//}

void simpleBuffer::replaceChar(char findChar, char replChar){
  int i;
  for (i=0; i<_len; i++) if(_buf[_baseOffset+i] == findChar) _buf[_baseOffset+i] = replChar;
  return;
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
 
long simpleBuffer::getHexDigitsAt(int offset, int limit){
    int j;
    int32_t w;
    w = (('0' <= getCharAt(offset) && getCharAt(offset) <= '7') ? 0 : 0xFFFFFFFF);
    for (j=0; j<limit; j++) {
        int8_t c = getCharAt(offset+j);
        c = (('0' <= c) && (c <= '9') ? c-'0' : (('A' <= c) && (c <= 'F') ? c - 'A' + 10 : -1));
        w = (w << 4) & 0xFFFFFFF0 | (c & 0xF);
    }
    
    return w;
  
}

void simpleBuffer::resetBaseOffset()
{
   _baseOffset = 0;
}

void simpleBuffer::setBaseOffset(int offset){
   _baseOffset = offset;
}


void simpleBuffer::setCharAt(int offset, char c){
    if (( _baseOffset + offset) < _len)  _buf[ _baseOffset+offset] = c;
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

void simpleBuffer::setSignedHexDigitsAt(int offset, long v, int limit) {
    setHexDigitsAt(offset, abs(v), limit);
    setCharAt(offset, (v < 0 ? '-' : '+'));  
}

void simpleBuffer::setHexDigitsAt(int offset, long v, int limit){
    int j;
    long w = v;
    for (j=limit-1; j>=0; j--){
        int8_t c = w & 0xF;
        setCharAt(offset+j, (c < 10 ? c + '0' : c - 10 + 'A'));
        w = w >> 4;
    }
}

void simpleBuffer::setHexByteAt(int offset, int v) {
    setHexDigitsAt(offset, v, 2);
}
