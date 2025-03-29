

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

void unsignedIntToBuf(int value, int maxsize, char vbuffer[]){
    dtostrf(abs(value), maxsize, 0, vbuffer);
    for (int i = 0; vbuffer[i] != 0; i++) {
    if (vbuffer[i] == ' ') vbuffer[i] = '0';
   }
}

void unsignedLongIntToBuf(long value, int maxsize, char vbuffer[]){
    dtostrf(abs(value), maxsize, 0, vbuffer);
    for (int i = 0; vbuffer[i] != 0; i++) {
    if (vbuffer[i] == ' ') vbuffer[i] = '0';
   }
}


void unsignedFloatToBuf(float value, int maxsize, int nbrdec, char vbuffer[]){
  dtostrf(abs(value), maxsize, nbrdec, vbuffer);
  for (int i = 0; vbuffer[i] != 0; i++) {
    if (vbuffer[i] == ' ') vbuffer[i] = '0';
   }
}


void signedFloatToBuf(float value, int maxsize, int nbrdec, char vbuffer[]){
  dtostrf(value, maxsize, nbrdec, vbuffer);
  for (int i = 0; vbuffer[i] != 0; i++) {
    if (vbuffer[i] == ' ' ) vbuffer[i] = '0';
    if (vbuffer[i] == '-') {vbuffer[i] = '0'; vbuffer[0] = '-' ;}
   }
  if (vbuffer[0] == '0') vbuffer[0] = '+';
}
