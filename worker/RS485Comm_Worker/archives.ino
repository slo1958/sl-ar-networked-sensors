/******************************************************************************
 
void hexacout(char v){
    int c; 
    c = v / 16;
    std::cout<< (c < 10 ? c + '0' : c - 10 + 'A');
    c = v % 16;
    std::cout<< (c < 10 ? c + '0' : c - 10 + 'A');
}

void hexacharcout(char v){
    char b[3];
    char c; 
    c = v / 16;
    b[0] =  (c < 10 ? c + '0' : c - 10 + 'A');
    c = v % 16;
    b[1] =  (c < 10 ? c + '0' : c - 10 + 'A');
    b[2] = 0;
    std::cout<< b;
}


void hexabufcout(const char v[], int len){
    for (int i = 0; i<len; i++) hexacharcout(v[i]);    
}





                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.



#include <iostream>
int calcxor(char b[], int len) {
    int r = 0;
    for (int i = 0; i<len;i++) { r = r ^ b[i];}
    return r & 0xFF;
    
}

int hextoint(char c){
    return   (('0' <= c) && (c <= '9') ? c-'0' : (('A' <= c) && (c <= 'F') ? c - 'A' + 10 : -1));
}

int calcxor2(char b[], int len) {
    int r = 0;
    int k = 0;
    int i;
    for (i = 0; ((i<len) && (b[i]!=':'));i++) { r = r ^ b[i];}
    if (b[i] != ':') return r & 0xFF;
    if (i+2 > len) return r & 0xFF;
    
    i++;
    k = hextoint(b[i]) * 16 + hextoint(b[i+1]);
    
//    std::cout<< (r & 0xFF);
//    std::cout<<'/';
//    std::cout<<k;
//    std::cout<<'/';  
    return (r & 0xFF) - k;
}

void hexacharcout(char v){
    char b[3];
    char c; 
    c = v / 16;
    b[0] =  (c < 10 ? c + '0' : c - 10 + 'A');
    c = v % 16;
    b[1] =  (c < 10 ? c + '0' : c - 10 + 'A');
    b[2] = 0;
    std::cout<< b;
}

void hexabufcout(const char v[], int len){
    for (int i = 0; i<len; i++) hexacharcout(v[i]);    
}

int main()
{
    char k[20] = "[Hello World";
    
    k[16] = ':';
    k[17] = '7';
    k[18] = 'B';
    k[19] = ']';
    
    
    std::cout<<"start:";
    hexacharcout(calcxor2(k, 20));

    return 0;
}

==============================




class commonBufferHandler{

  public:
    commonBufferHandler();
    virtual void clearBuffer();
    bool anyDataInBuffer();

    int exchangeBetweenBuffers(char inbuffer[], char outBuffer[], int startInPosition, int startOutPosition);

    bool getBooleanAt(int offset);
    char getCharAt(int charIndex);
    int getDigitAt(int offset);
    int getHexDigitAt(int offset);
    int getHexByteAt(int offset);
    int getUnsignedIntAt(int offset, int count, bool inverted);
    long getUnsignedLongAt(int offset, int count, bool inverted);

    int getFromBuffer(int offset, char outBuffer[]);
    
    void setBooleanAt(int offset,bool v);
    void setCharAt(int offset, char cc);
    void setDigitAt(int offset, int v);
    void setHexDigitAt(int offset, int v);

    void setHexByteAt(int offset, byte v);

    
    void setHexBytesAt(int offset, byte value[], int vsize);


    int putToBuffer(int offset, char inBuffer[]);
    
//    int putConvertedToBuffer(int offset);
    
//    char conversionBuffer[20];
    
  protected:
    char _Buffer[BUFFER_SIZE];
    int _BufferIndex;
};




//=======================

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
 




*******************************************************************************/
