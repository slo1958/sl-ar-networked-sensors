
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

#define XBUF_SIZE 32

char xbuf[XBUF_SIZE];

int extractCheckedAddress(int startbyte) {
  int k1 = getBufferIntAt(startbyte, 3, false);
  if (k1 < 0) return -1;

  int k2 = getBufferIntAt(startbyte + 3, 3, true);
  if (k2 < 0) return -1;

  if (k1 != k2) return -1;
  return k1;
}

void writeReply() {
  startWriting();
  
  Serial.print(outputBuffer);

  doneWriting();

  clearInputBuffer();
  clearOutputBuffer();
}

void addAddressToOutputBuffer(int addr) {

  addToOutputBuffer('A');
       
  clearBuffer(xbuf, XBUF_SIZE);
  unsignedIntToBuf(addr,3, xbuf);
  moveToOutputBuffer(xbuf);

  addToOutputBuffer(':');
  addToOutputBuffer('X');
      
  clearBuffer(xbuf, XBUF_SIZE);
  unsignedIntToBuf(999-addr,3, xbuf);
  moveToOutputBuffer(xbuf);
  return;
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

  clearOutputBuffer();
  int addr = extractCheckedAddress(ADDRESS_START);
    
  if (cmd == 'A') {
    if (!digitalRead(BUTTON_IO)) {
      lastError = ERR_CANNOT_SET_ADDRESS;
      clearInputBuffer();
      return;
    }
    // Set device address
    if ((1 <= addr) && (addr <= 250)) {
      int old_addr = DeviceID;
      EEPROM.write(EEPROMAddress_DeviceID, addr);
      DeviceID = addr;
      
      addToOutputBuffer('R');

      addAddressToOutputBuffer(addr);

      addToOutputBuffer(':');

      addToOutputBuffer('O');
       
      clearBuffer(xbuf, XBUF_SIZE);
      unsignedIntToBuf(old_addr,3, xbuf);
      moveToOutputBuffer(xbuf);

      addToOutputBuffer(';');   
      
      writeReply();

      clearInputBuffer();
      return;
    }

    moveToOutputBuffer("RE0:X99;");
    
    writeReply();

    lastError = ERR_INVALID_ADDRESS;
    clearInputBuffer();
    return;

  } else if ((cmd == 'D') && (addr == DeviceID)){
    
      float t = getTemperature();

      addToOutputBuffer('R');

      addAddressToOutputBuffer(addr);

      addToOutputBuffer(':');
      
      addToOutputBuffer('T');
      
      clearBuffer(xbuf, XBUF_SIZE);
      signedFloatToBuf(t, 8, 3, xbuf);
      moveToOutputBuffer(xbuf);

      addToOutputBuffer(':');

      addToOutputBuffer('X');
      
      clearBuffer(xbuf, XBUF_SIZE);
      signedFloatToBuf(999.999 - abs(t), 8, 3, xbuf);
      moveToOutputBuffer(xbuf);

      addToOutputBuffer(';');
     
      writeReply();

      lastError = 0;
      return;

  } else if ((cmd == 'P')  && (addr == DeviceID)) {

      addToOutputBuffer('R');

      addAddressToOutputBuffer(addr);

      addToOutputBuffer(';');
      
      writeReply();
      
      lastError = 0;
      return;
     
  } else if ((cmd == 'S')  && (addr == DeviceID)) {
      addToOutputBuffer('R');

      addAddressToOutputBuffer(addr);

      addToOutputBuffer(':');

      addToOutputBuffer('S');

      if (SensorDeviceFound) {
 
        clearBuffer(xbuf, XBUF_SIZE);
        bytesToHexBuf(SensorAddress, 8, xbuf);

        moveToOutputBuffer(xbuf);
        
      } else {
        
        addToOutputBuffer('0');

      }
      
      addToOutputBuffer(':');

      addToOutputBuffer('P');
      
      clearBuffer(xbuf, XBUF_SIZE);
      booleanToBuf(SensorParasitePower, xbuf);
      
      moveToOutputBuffer(xbuf);
      
      addToOutputBuffer(':');

      addToOutputBuffer('V');
      
      moveToOutputBuffer(SOFTWARE_VERSION);
 
      addToOutputBuffer(';');
 
      writeReply();
      
      return;

  } else if   (addr == DeviceID) {
     moveToOutputBuffer("RE1:X98;");
     
     writeReply();
      
     lastError = ERR_INVALID_COMMAND;
     clearInputBuffer();
     return;
  }

}
//Sketch uses 11732 bytes (38%) of program storage space. Maximum is 30720 bytes.
//Global variables use 647 bytes (31%) of dynamic memory, leaving 1401 bytes for local variables. Maximum is 2048 bytes.
