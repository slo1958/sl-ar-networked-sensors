
// Set Address command is enabled in normal mode if DI5 (BUTTON_IO) becomes high after setup, 
// this will also clear the latest error indication
//
// Current address is not tested when using the 'A' command because it is assumed that it could be unknown.
// User must make sure only one node has its BUTTON_IO high.
//
//
// Message structure
// Command from master to device   CxAAABBB;
// Reply from device to master
//       R<element>:<element>: ... ;
// AAA: device address
// BBB: 999 - device address
//
// x = Commands
// A: set device address (001 to 250), current address is not tested and BUTTON_IO must be set high after setup
// S: get device status
// D: get device data
// P: poll device
//
// Reply element
// A<value> : address
// X<value> : Complement from abs(previous value) (against 999 for address, 999.999 for temperature)
// S<value> : Sensor address or id
// P<value> : Sensor parasite power
// T<value> : temperature
//
// Example
// CS111888; get status from device address 111
// RA111:S2889518500000062:P0;
//
// CD111888;get status from device address 111
// RT21.56:X978.44;
//
// CA222777; set device address to 222 (this works only if BUTTON_IO is high)
// RA222:X777;
//



int extractCheckedAddress(int startbyte) {
  int k1 = getBufferIntAt(startbyte, 3, false);
  if (k1 < 0) return -1;

  int k2 = getBufferIntAt(startbyte + 3, 3, true);
  if (k2 < 0) return -1;

  if (k1 != k2) return -1;
  return k1;
}


void processCommand() {
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

  int addr = extractCheckedAddress(ADDRESS_START);
    
  if (cmd == 'A') {
    if (!digitalRead(BUTTON_IO)) {
      lastError = ERR_CANNOT_SET_ADDRESS;
      clearInputBuffer();
      return;
    }
    // Set device address
    if ((1 <= addr) && (addr <= 250)) {
      EEPROM.write(EEPROMAddress_DeviceID, addr);
      DeviceID = addr;

      startWriting();
      Serial.print('R');
      Serial.print('A');
      Serial.print(addr);
      Serial.print(':');
      Serial.print('X');
      Serial.print(999 - addr);
      Serial.print(';');
      doneWriting();

      clearInputBuffer();
      return;
    }

    startWriting();
    Serial.print("RE0:X99;");
    doneWriting();

    lastError = ERR_INVALID_ADDRESS;
    clearInputBuffer();
    return;

  } else if ((cmd == 'D') && (addr == DeviceID)){
    
      float t = getTemperature();
      startWriting();
      Serial.print('R');
      Serial.print('A');
      Serial.print(addr);
      Serial.print(':');
      Serial.print('X');
      Serial.print(999 - addr);
      Serial.print('T');
      Serial.print(t);
      Serial.print(':');
      Serial.print('X');
      Serial.print(999.999 - abs(t));
      Serial.print(';');
      doneWriting();
    
      clearInputBuffer();
      lastError = 0;
      return;

  } else if ((cmd == 'S')  && (addr == DeviceID)) {
 
      startWriting();
      Serial.print('R');
      Serial.print('A');
      Serial.print(addr);
      Serial.print(':');
      Serial.print('X');
      Serial.print(999 - addr);
      Serial.print(':');
      Serial.print('S');
      if (SensorDeviceFound) {
        char xbuf[32]; 
        bytesToHexBuf(SensorAddress, 8, xbuf);
        Serial.print(xbuf);
      }
      Serial.print(':');
      Serial.print('P');
      Serial.print(SensorParasitePower);
      Serial.print(';');
      doneWriting();
   
      clearInputBuffer();
      return;

  } else if   (addr == DeviceID) {
     Serial.print("RE1:X98;");
     lastError = ERR_INVALID_COMMAND;
     clearInputBuffer();
     return;
  }

}
