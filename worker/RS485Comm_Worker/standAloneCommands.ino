

//
//Stand alone command
//
//  CxY
//
// x = commands
//
// A : update address
// Format: CAyyy;
// yyy is address between 001 .. 250
//
// P : enable/disable repeat polling of temperature
// Format: Py; 
// 0 (off) or 1 (on)
//
// S : show status
// Format: S;
//

void printBoolean(bool value, String TextIfFalse, String TextIfTrue) {
  if (value) {
    Serial.print(TextIfTrue);
  }
  else {
    Serial.print(TextIfFalse);
  }
}

void pollTemperature() {
  Serial.print("Temperature: ");
  Serial.print(getTemperature());
  Serial.println("°C");
}


void printStandAloneStatus() {
  
  Serial.print("Found ");
  Serial.print(SensorCount, DEC);
  Serial.println(" sensor(s).");
  
  Serial.print("Device address ");
  Serial.print(DeviceID);
  Serial.println(".");
  
  Serial.print("Version: ");
  Serial.print(SOFTWARE_VERSION);
  Serial.println(".");
    
  Serial.print("Parasite pwr: ");
  printBoolean(SensorParasitePower, "OFF", "ON");
  Serial.println(".");

  Serial.print("Polling: ");
  printBoolean(AutoPollingMode, "OFF", "ON");
  Serial.println(".");
    
  Serial.print("Sensor address ");
  printBoolean(SensorDeviceFound, "not found", "is ");
  if (SensorDeviceFound) {
     char xbuf[32]; 
     clearBuffer(xbuf, 32);
     bytesToHexBuf(SensorAddress, 8, xbuf);
     Serial.print(xbuf);
  }
  Serial.println(".");
}


void processStandAloneCommand() {
  //
  // The input buffer is locked, we received a ';'
  //
  // First character is the command
  //
  char msgType = inputBuffer[0];
  char cmd = inputBuffer[1];
  if (msgType != 'C') {
    clearInputBuffer();
    return;
  }

  if (cmd == 'A') {
    // Set device address
    int addr = getBufferIntAt(ADDRESS_START, 3, false);
    if ((1 <= addr) && (addr <= 250)) {
      EEPROM.write(EEPROMAddress_DeviceID, addr);
      Serial.print("Device address updated from ");
      Serial.print(DeviceID);
      Serial.print(" to ");
      Serial.print(addr);
      Serial.println('.');
      DeviceID = addr;
      clearInputBuffer();
      return;
    } else {
      Serial.print("Invalid device address ");
      Serial.print(addr);
      Serial.println('.');
      clearInputBuffer();
      return;
    }
  } else if (cmd == 'P') {
    if (getBufferFlagAt(2) >= 0) AutoPollingMode = getBufferFlagAt(2);
    clearInputBuffer();
    Serial.print("Polling mode is now ");
    Serial.print(AutoPollingMode);
    Serial.println('.');
  } else if (cmd == 'S') {
    clearInputBuffer();
    printStandAloneStatus();
  } else {
    Serial.print("Command error.");
    Serial.println();
    clearInputBuffer();
    return;
  }

}
