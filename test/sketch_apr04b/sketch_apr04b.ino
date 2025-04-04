
#include "InputBufferLib2.h"

inputBufferHardSerial myInput();
inputBufferSoftSerial rsNetwork(9,8);

#include <SoftwareSerial.h>
SoftwareSerial* mySerial;

void setup() {
  // put your setup code here, to run once:
  mySerial = &SoftwareSerial(1,2);
}

void loop() {
  int i=0;
  // put your main code here, to run repeatedly:
  if (mySerial->available()) i=1;
}
