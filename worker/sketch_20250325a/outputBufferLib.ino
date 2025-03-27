char outputBuffer[OUTPUT_BUFFER_SIZE];

void clearOutputBuffer() {
 // for (int i = 0; i < OUTPUT_BUFFER_SIZE; i++) outputBuffer[i] = 0;
  clearBuffer(outputBuffer, OUTPUT_BUFFER_SIZE);
}

void clearBuffer(char vbuffer[], int buffersize) {
   for (int i = 0; i < buffersize; i++) vbuffer[i] = 0; 
}

int moveToOutputBuffer(char vbuffer[], int startposition) {
   int i=0;
   for (i=0; vbuffer[i] != 0; i++) outputBuffer[startposition+i] = vbuffer[i];
   outputBuffer[startposition+i] = 0;
   return startposition + i; 
}
