#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "InputBufferLib2.h"

#define SOFTWARE_VERSION "0.0.008"

// Data wire is connected to GPIO 4
#define ONE_WIRE_BUS_IO 4

#define BUTTON_IO 5

#define SERIAL_CTRL_IO 6

#define EEPROMAddress_DeviceID 1
#define AUTO_CLEAR_BUFFER_DELAY 10000


#define SOFT_SERIAL_TX_IO 8
#define SOFT_SERIAL_RX_IO 9


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


byte DeviceID = 255;

OneWire oneWire(ONE_WIRE_BUS_IO);
DallasTemperature sensors(&oneWire);
DeviceAddress SensorAddress;

bool ledStatus = HIGH;
unsigned long ledLastChange;
unsigned long ledChangeDelay;
unsigned long pollLastRun = 0;
 
byte lastError = 0;

bool SensorParasitePower;
bool SensorDeviceFound;
bool AutoPollingMode = false;
bool HasSerialMonitor = false;
int SensorCount = 0;

 

inputBufferHardSerial serialMonitor(1);
inputBufferSoftSerial rsNetwork(SOFT_SERIAL_RX_IO, SOFT_SERIAL_TX_IO); // RX, TX


void setup(void) {

  ledLastChange = millis();

  //initSerialControl();
  
  pinMode(BUTTON_IO, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  HasSerialMonitor = digitalRead(BUTTON_IO);

  //mySerial.begin(9600);

  DeviceID = EEPROM.read(EEPROMAddress_DeviceID);
  
  if (HasSerialMonitor) {
    Serial.begin(9600);
    Serial.println("Starting...");
  }

  sensors.begin();

  SensorCount = sensors.getDeviceCount();

  SensorParasitePower = sensors.isParasitePowerMode();
  SensorDeviceFound = sensors.getAddress(SensorAddress, 0);

    rsNetwork.clearInputBuffer();
    serialMonitor.clearInputBuffer();

   

  if (HasSerialMonitor) {
    printStandAloneStatus();
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


#define ADDRESS_START 2
 
void HandleSerialMonitor() {
  if (AutoPollingMode) {
    if ((millis() - pollLastRun ) > 1000) {
      pollTemperature();
      pollLastRun = millis();
    }
  }
  serialMonitor.checkAnyMessage();
  if (serialMonitor.inputCommandReady())  processStandAloneCommand();
}

int lastButtonState;

void HandleNormalMode() {
  // ledChangeDelay = LED_DELAY_OFF;
  
  rsNetwork.checkAnyMessage();

  if (rsNetwork.inputCommandReady()) processCommand();

  if (lastError != 0) ledChangeDelay = LED_DELAY_ERROR;

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
  serialMonitor.clearOldData(AUTO_CLEAR_BUFFER_DELAY);
  rsNetwork.clearOldData(AUTO_CLEAR_BUFFER_DELAY);
 

  if (HasSerialMonitor) HandleSerialMonitor();
  
    HandleNormalMode();
  

  if (ledChangeDelay > 0) {
    updateLED();
    delay(50);
  } else if (anyDataInInputBuffer()) {
    updateLED();
    delay(50);
  } else {
    updateLED();
    delay(1000);
  }

}
