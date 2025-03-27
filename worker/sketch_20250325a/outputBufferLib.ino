char outputBuffer[OUTPUT_BUFFER_SIZE];

int outIndex = 0;

void clearOutputBuffer() {
 // for (int i = 0; i < OUTPUT_BUFFER_SIZE; i++) outputBuffer[i] = 0;
  clearBuffer(outputBuffer, OUTPUT_BUFFER_SIZE);
  outIndex = 0;
}

void clearBuffer(char vbuffer[], int buffersize) {
   for (int i = 0; i < buffersize; i++) vbuffer[i] = 0; 
}

void moveToOutputBuffer(char vbuffer[]) {
  outIndex = moveToBuffer(vbuffer, outputBuffer, outIndex);
}

int moveToBuffer(char inbuffer[], char outBuffer[], int startposition) {
   int i=0;
   for (i=0; inbuffer[i] != 0; i++) outBuffer[startposition+i] = inbuffer[i];
   outBuffer[startposition+i] = 0;
   return startposition + i; 
}

void addToOutputBuffer(char cc){
  outputBuffer[outIndex] = cc;
  outputBuffer[outIndex+1] = 0;
  outIndex = outIndex+1;
}
