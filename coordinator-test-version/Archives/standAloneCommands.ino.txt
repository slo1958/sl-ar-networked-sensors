

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


void processStandAloneCommand(inputBufferHandler p) {
  //
  // The input buffer is locked, we received a ';'
  //
  // First character is the command
  //
  char msgType = p.getCharAt(0);
  char cmd =  p.getCharAt(1);
  if (msgType != 'C') {
    p.clearBuffer();
    return;
  }

  if (cmd == 'A') {
    // Set device address
    int addr = p.getUnsignedIntAt(ADDRESS_START, 3, false);
    if ((1 <= addr) && (addr <= 250)) {
      EEPROM.write(EEPROMAddress_DeviceID, addr);
      Serial.print("Device address updated from ");
      Serial.print(DeviceID);
      Serial.print(" to ");
      Serial.print(addr);
      Serial.println('.');
      DeviceID = addr;
      p.clearBuffer();
      return;
    } else {
      Serial.print("Invalid device address ");
      Serial.print(addr);
      Serial.println('.');
      p.clearBuffer();
      return;
    }
  } else if (cmd == 'P') {
    if (p.getDigitAt(2) >= 0) AutoPollingMode = p.getDigitAt(2);
    p.clearBuffer();
    Serial.print("Polling mode is now ");
    Serial.print(AutoPollingMode);
    Serial.println('.');
  } else if (cmd == 'S') {
    p.clearBuffer();
    printStandAloneStatus();
  } else {
    Serial.print("Command error.");
    Serial.println();
    p.clearBuffer();
    return;
  }

}
