

void bytesToHexBuf(byte value[], int intsize, char vbuffer[]){
  int j = 0;

  for (int i=0; i<intsize; i++) {
    unsigned int n = value[i];
 
    byte c = n % 16;
    vbuffer[j+1] = (c < 10 ? c + '0' : c - 10 + 'A');
    c = n / 16;
    vbuffer[j] = (c < 10 ? c + '0' : c - 10 + 'A');
    j += 2;
    
    }
}


void booleanToBuf(bool value, char vbuffer[]){
  vbuffer[0] = (value ? '1' : '0');
  vbuffer[1] = 0;
}


void unsignedIntToBuf(int value, int minsize, char vbuffer[]){
  // dtostrf() adds a binary zero at the end of the string
    dtostrf(abs(value), minsize, 0, vbuffer);
    for (int i = 0; vbuffer[i] != 0; i++) {
    if (vbuffer[i] == ' ') vbuffer[i] = '0';
   }
}

void unsignedLongIntToBuf(long value, int minsize, char vbuffer[]){
    dtostrf(abs(value), minsize, 0, vbuffer);
    for (int i = 0; vbuffer[i] != 0; i++) {
    if (vbuffer[i] == ' ') vbuffer[i] = '0';
   }
}


void unsignedFloatToBuf(float value, int minsize, int nbrdec, char vbuffer[]){
  // dtostrf prefixes the string generated from the converted value with spaces to reach minsize
  // Make sure that the buffer is 'big enough' to accomodate the string, because dtostrf will extend beyond minsize if needed
  // Minimum value for minsize
  //  1 byte for the sign if value is < 0
  //  'enough' bytes for the integer for the integer part
  //  1 byte for the decimal mark '.'
  //  nbr dec bytes for decimal part
  //  1 byte for trailing \0
  
  dtostrf(abs(value), minsize, nbrdec, vbuffer);
  for (int i = 0; vbuffer[i] != 0; i++) {
    if (vbuffer[i] == ' ') vbuffer[i] = '0';
   }
}


void signedFloatToBuf(float value, int minsize, int nbrdec, char vbuffer[]){
  dtostrf(value, minsize, nbrdec, vbuffer);
  for (int i = 0; vbuffer[i] != 0; i++) {
    if (vbuffer[i] == ' ' ) vbuffer[i] = '0';
    if (vbuffer[i] == '-') {vbuffer[i] = '0'; vbuffer[0] = '-' ;}
   }
  if (vbuffer[0] == '0') vbuffer[0] = '+';
}
