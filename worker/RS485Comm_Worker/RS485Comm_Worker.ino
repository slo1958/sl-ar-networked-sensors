#include <OneWire.h>
#include <DallasTemperature.h>

#include <SoftwareSerial.h>
#include "SerialComm.h"
#include "InputBufferLib2.h"
#include "OutputBufferLib2.h"
#include "CustomDeviceAndNode.h"

#define SOFTWARE_VERSION "0.0.008"

// Data wire is connected to GPIO 4
#define ONE_WIRE_BUS_IO 4

#define BUTTON_IO 5



#define AUTO_CLEAR_BUFFER_DELAY 10000


#define SOFT_SERIAL_TX_IO 8
#define SOFT_SERIAL_RX_IO 9


#define SERIAL_CTRL_IO 6
#define SERIAL_CTRL_READ 0
#define SERIAL_CTRL_WRITE 1

#define ERR_CANNOT_SET_ADDRESS 21
#define ERR_INVALID_ADDRESS 22
#define ERR_INVALID_COMMAND 23

#define LED_DELAY_STANDALONE 1500
#define LED_DELAY_ERROR 200
#define LED_DELAY_SIGNAL 100
#define LED_DELAY_SETUP_ADDRESS 500
#define LED_DELAY_OFF 0

#define INPUT_BUFFER_SIZE 32
#define OUTPUT_BUFFER_SIZE 64

// Local mode is activated if DI5 (BUTTON_IO) is high during setup
// Set Address command is enabled in normal mode if DI5 (BUTTON_IO) becomes high after setup, 
// this will also clear the latest error indication

#define KBUFFER_SIZE 32

OneWire oneWire(ONE_WIRE_BUS_IO);
DallasTemperature sensors(&oneWire);
DeviceAddress SensorAddress;

customNodeDefinition currentNode;

bool hasUserControl = false;


bool ledStatus = HIGH;
unsigned long ledLastChange;
unsigned long ledChangeDelay;
unsigned long pollLastRun = 0;
 
byte lastError = 0;

bool SensorParasitePower;
bool SensorDeviceFound;
bool AutoPollingMode = false;

int SensorCount = 0;

char commInBuffer[KBUFFER_SIZE];
char commOutBuffer[KBUFFER_SIZE];
char rsNetInBuffer[KBUFFER_SIZE];
char rsNetOutBuffer[KBUFFER_SIZE];

hardwareSerial userControlSerial;
softwareSerial rsNetworkSerial(SOFT_SERIAL_RX_IO, SOFT_SERIAL_TX_IO); // RX, TX

inputBufferHandler userControlInput(userControlSerial, commInBuffer, KBUFFER_SIZE);
outputBufferHandler userControlOutput(userControlSerial, commOutBuffer, KBUFFER_SIZE);

inputBufferHandler rsNetworkInput(rsNetworkSerial, rsNetInBuffer, KBUFFER_SIZE);
outputBufferHandler rsNetworkOutput(rsNetworkSerial, rsNetOutBuffer, KBUFFER_SIZE);

void setup(void) {
  
  ledLastChange = millis();
  ledChangeDelay = LED_DELAY_OFF;

  rsNetworkSerial.setReadWriteControl(SERIAL_CTRL_IO, SERIAL_CTRL_READ, SERIAL_CTRL_WRITE);
  
  pinMode(BUTTON_IO, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  hasUserControl = digitalRead(BUTTON_IO);

  rsNetworkSerial.xbegin(9600);

  
  if (hasUserControl) {
    userControlSerial.xbegin(9600);
  }

  currentNode.configureCustomNode();

  sensors.begin();

  SensorCount = sensors.getDeviceCount();

  SensorParasitePower = sensors.isParasitePowerMode();
  SensorDeviceFound = sensors.getAddress(SensorAddress, 0);

  rsNetworkInput.clearBuffer();
  rsNetworkOutput.clearBuffer();
  userControlInput.clearBuffer();
  userControlOutput.clearBuffer();
   

  if (hasUserControl) {
    printStatus(userControlOutput);
  }

}



float getTemperature() {
  sensors.requestTemperatures();
  delay(750);
  float tempC = sensors.getTempCByIndex(0);
  return tempC;
}


boolean debounce(int IOPin, boolean prev) {
  boolean cur = digitalRead(IOPin);

  if (prev != cur) {
    delay(5);
    cur = digitalRead(IOPin);
    return cur;
  }
}

void updateLED() {
  unsigned long timeSinceLastChange;

  if (ledChangeDelay < 1) {
    digitalWrite(LED_BUILTIN, LOW);
    return;
  }
  timeSinceLastChange = millis() - ledLastChange;

  if (timeSinceLastChange > ledChangeDelay) {
    ledStatus = !ledStatus;
    digitalWrite(LED_BUILTIN, ledStatus);
    ledLastChange = millis();
  }

  if (timeSinceLastChange < 0 ) ledLastChange = millis();
}


// 
 

int lastButtonState;

void checkButton() {
  if (digitalRead(BUTTON_IO))  {
    ledChangeDelay = LED_DELAY_SETUP_ADDRESS;
    lastError = 0;
    lastButtonState = true;
  } else if (lastButtonState) {
    lastButtonState = false;
    ledChangeDelay = LED_DELAY_OFF;
  }
  
}

void loop(void) {
  userControlInput.clearOldData(AUTO_CLEAR_BUFFER_DELAY);
  rsNetworkInput.clearOldData(AUTO_CLEAR_BUFFER_DELAY);
 
  processControl(userControlInput, userControlOutput);

  processCommand(currentNode, rsNetworkInput, rsNetworkOutput, hasUserControl);
 
  if (lastError != 0) ledChangeDelay = LED_DELAY_ERROR;
  
  updateLED();
  
  delay(100);
}
