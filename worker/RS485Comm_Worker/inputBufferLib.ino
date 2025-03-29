
char inputBuffer[INPUT_BUFFER_SIZE];
int inputBufferIndex;
bool inputBufferLocked;

unsigned long lastInputBufferReset;

bool anyDataInInputBuffer() {return inputBufferIndex > 0; }

bool inputCommandReady() {return inputBufferLocked; }

long inputBufferAge() {return millis() - lastInputBufferReset;}

void clearInputBuffer() {
  for (int i = 0; i < INPUT_BUFFER_SIZE; i++) inputBuffer[i] = 0;
  inputBufferLocked = false;
  inputBufferIndex = 0;
  lastInputBufferReset = millis();
}

void checkAnyMessage() {
  if (inputBufferLocked) return;

  while (Serial.available() > 0) {
    char x = Serial.read();
    if (!isControl(x)) {
      inputBuffer[inputBufferIndex] = x;
      inputBufferLocked = (x == ';');
      
      if (x == '*') {
        clearInputBuffer();
        inputBufferLocked = false;
      } else if (inputBufferIndex < INPUT_BUFFER_SIZE) inputBufferIndex += 1;              

     
     lastInputBufferReset = millis();
     }    
  }
}
//void checkAnyMessage() {
//  if (inputBufferLocked) return;
//
//  while (Serial.available() > 0) {
//    char x = Serial.read();
//    if (!isControl(x)) {
//      inputBuffer[inputBufferIndex] = x;
//      inputBufferLocked = (x == ';');
//      if (inputBufferIndex < INPUT_BUFFER_SIZE) inputBufferIndex += 1;
//      lastInputBufferReset = millis();
//    }
//
//  }
//}


int getBufferFlagAt(int offset) {
  char x;
  if (offset > INPUT_BUFFER_SIZE) return -1;
  if (offset > inputBufferIndex) return -1;
  x = inputBuffer[offset];
  if (isdigit(x)) return x - '0';
  return -1;
}


int getBufferIntAt(int offset, int count, bool inverted) {
  int k1 = 0;
  for (int i = offset; i < offset + count; i++) {
    if (i <= inputBufferIndex) {
      char x = inputBuffer[i];
      if (isDigit(x)) {
        k1 = k1 * 10 + (inverted ? (9 - (x - '0')) :  (x - '0'));
      } else return -1;
    } else return -1;
  }
  return k1;
}
