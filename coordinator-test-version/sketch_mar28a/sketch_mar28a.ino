
//Note:
// Not all pins on the Mega and Mega 2560 support change interrupts,
// so only the following can be used for RX:
// 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 6
//
// We use SoftSerial for the netowrk part and the hardware serial for console interaction.

#define SERIAL_PASS_THROUGH true

#define SOFT_SERIAL_TX_IO 8
#define SOFT_SERIAL_RX_IO 9

#include <SoftwareSerial.h>


#define INPUT_BUFFER_SIZE 32
#define OUTPUT_BUFFER_SIZE 64

#define SERIAL_CTRL_IO 6
#define SERIAL_CTRL_READ 0
#define SERIAL_CTRL_WRITE 1

SoftwareSerial mySerial(SOFT_SERIAL_RX_IO, SOFT_SERIAL_TX_IO); // RX, TX
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  mySerial.begin(9600);

  Serial.println("Ready");
  clearInputBuffer();
  initSerialControl();
  
}

void normalOperations(){
}

void serialPassThrough(){
 if (mySerial.available())
    Serial.write(mySerial.read());

  checkAnyMessage();

  if (inputCommandReady()) {
      echoInputBuffer();
      writeInputBuffer();
      clearInputBuffer();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (SERIAL_PASS_THROUGH) serialPassThrough(); else normalOperations(); 
  
}
