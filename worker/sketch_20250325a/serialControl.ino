
//
// Expects the following defines:
//
// #define SERIAL_CTRL_IO x
// #define SERIAL_CTRL_READ 0
// #define SERIAL_CTRL_WRITE 1
//

void initSerialControl(){
    pinMode(SERIAL_CTRL_IO, OUTPUT);
    digitalWrite(SERIAL_CTRL_IO, SERIAL_CTRL_READ);
}

void startWriting() {
  digitalWrite(SERIAL_CTRL_IO, SERIAL_CTRL_WRITE);
  delay(5);
}

void doneWriting() {
  Serial.flush();
  delay(5);
  digitalWrite(SERIAL_CTRL_IO, SERIAL_CTRL_READ);
}
