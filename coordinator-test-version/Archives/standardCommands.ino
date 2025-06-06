
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
// D: get device data
// F: Flash led (reset if address is not matching)
// P: poll device
// S: get device status
//
// Reply element
// A<value> : address
// L<value> : Led delay
// P<value> : Sensor parasite power
// S<value> : Sensor address or id
// T<value> : temperature
// V<value> : Software version
// X<value> : Complement from abs(previous value) (against 999 for address, 999.999 for temperature)
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




void writeReply() {
  startWriting();
  
  // mySerial.print(outputBuffer);

  doneWriting();

  clearOutputBuffer();
}


void writeError(byte errCode) {
      addToOutputBuffer('R');

      addAddressToOutputBuffer(DeviceID);

      addToOutputBuffer(':');

      addToOutputBuffer('E');

      clearBuffer(xbuf, XBUF_SIZE);
      unsignedIntToBuf(errCode,2, xbuf);
      moveToOutputBuffer(xbuf);
      
      addToOutputBuffer(':');

      addToOutputBuffer('X');
      
      clearBuffer(xbuf, XBUF_SIZE);
      unsignedIntToBuf(99-errCode,2, xbuf);
      moveToOutputBuffer(xbuf);      
      
      endOutputBuffer();

      writeReply();

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

void writeStatusReply(int addr){
  
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

      addToOutputBuffer(':');

      addToOutputBuffer('L');

      clearBuffer(xbuf, XBUF_SIZE);
      unsignedLongIntToBuf(ledChangeDelay,6, xbuf);
      moveToOutputBuffer(xbuf);
      
      addToOutputBuffer(':');     
      
      clearBuffer(xbuf, XBUF_SIZE);
      unsignedLongIntToBuf(999999-ledChangeDelay,6, xbuf);
      moveToOutputBuffer(xbuf);

      endOutputBuffer();
 
      writeReply();

}

void writeFlashReply(int addr) {
      addToOutputBuffer('R');

      addAddressToOutputBuffer(addr);

      addToOutputBuffer(':');
          
      addToOutputBuffer('F');  
      
      endOutputBuffer();
 
      writeReply(); 
     
}

void writePollReply(int addr){
      addToOutputBuffer('R');

      addAddressToOutputBuffer(addr);

      endOutputBuffer();
      
      writeReply();
      
}


void writeAddressUpdateReply(int old_addr, int addr){
      addToOutputBuffer('R');

      addAddressToOutputBuffer(addr);

      addToOutputBuffer(':');

      addToOutputBuffer('O');
       
      clearBuffer(xbuf, XBUF_SIZE);
      unsignedIntToBuf(old_addr,3, xbuf);
      moveToOutputBuffer(xbuf);

      endOutputBuffer();   
      
      writeReply();

}


void processCommand(inputBufferHandler p, outputBufferHandler q) {
  //
  // The input buffer is locked, we received a ';'
  //
  // First character is the command
  //
  
  char msgType = p.getCharAt(0);
  char cmd = p.getCharAt(1); 
  
  if (msgType != 'C') {
    p.clearBuffer();
    return;
  }
  
  clearOutputBuffer();
  int addr = p.extractCheckedAddress(ADDRESS_START);
    
  if (cmd == 'A') {
    if (!digitalRead(BUTTON_IO)) {
      lastError = ERR_CANNOT_SET_ADDRESS;
      if (addr == DeviceID) writeError(ERR_CANNOT_SET_ADDRESS); 
      p.clearBuffer();
      return;
    }
    // Set device address
    if ((1 <= addr) && (addr <= 250)) {
      int old_addr = DeviceID;
      EEPROM.write(EEPROMAddress_DeviceID, addr);
      DeviceID = addr;

      writeAddressUpdateReply(old_addr, addr);
      p.clearBuffer();
      
    } else {
      lastError = ERR_INVALID_ADDRESS;    
    }

    p.clearBuffer();
    return;
    
  } else if (cmd == 'F') {
      ledChangeDelay = (  (addr == DeviceID) ? LED_DELAY_SIGNAL  : LED_DELAY_OFF) ;
      if (addr == DeviceID) writeFlashReply(addr);
      
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

      endOutputBuffer();
     
      writeReply();
      p.clearBuffer();
      lastError = 0;
      return;

  } else if ((cmd == 'P')  && (addr == DeviceID)) {

      writePollReply(addr);
      p.clearBuffer();
      lastError = 0;
      return;
     
  } else if ((cmd == 'S')  && (addr == DeviceID)) {
     
      writeStatusReply(addr);
      p.clearBuffer();
      lastError = 0;
      return;

  } else if (addr == DeviceID) {

      writeError(ERR_INVALID_COMMAND);
      
      lastError = ERR_INVALID_COMMAND;
      
      p.clearBuffer();      
      return;
  }

}
//Sketch uses 11732 bytes (38%) of program storage space. Maximum is 30720 bytes.
//Global variables use 647 bytes (31%) of dynamic memory, leaving 1401 bytes for local variables. Maximum is 2048 bytes.
