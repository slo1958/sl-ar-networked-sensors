#include "DeviceAndNode.h"
#include "InputBufferLib2.h"
#include "OutputBufferLib2.h"

// Protocol message layout

#define END_BUFFER_MARK ';'

#define TYPE_COMMAND 'C'
#define TYPE_SETADDRESS 'A'
#define TYPE_RESTART 'Z'

#define CMD_RESTART_NODE 'Z'
#define CMD_START_FLASH_LED 'F'
#define CMD_STOP_FLASH_LED 'G'
#define CMD_GET_REGISTER_DESCRIPTION 'D'
#define CMD_GET_REGISTER_VALUE 'V'
#define CMD_SET_REGISTER_VALUE 'W'

#define ADDRESS_START 1
#define CMD_START 5
#define REPLY_PAYLOAD_START 6

#define CMD_OK 0
#define ERR_CANNOT_SET_ADDRESS 21

void prepareReplyHeader(nodeDefinition node, outputBufferHandler outbuf){
  outbuf.clearBuffer();
  outbuf.setCharAt(0, 'R');
  outbuf.setHexByteAt(1, node.getNodeAddr());
  outbuf.setHexByteAt(3, 255 - node.getNodeAddr());
  outbuf.setCharAt(5,':');
  
}

void prepareReplyUpdateAddress(nodeDefinition node, outputBufferHandler outbuf, int oldAddress, int opStatus){
  prepareReplyHeader(node, outbuf);
  outbuf.setCharAt(REPLY_PAYLOAD_START,'A');
  outbuf.setHexByteAt(REPLY_PAYLOAD_START + 1, oldAddress);
  outbuf.setHexByteAt(REPLY_PAYLOAD_START + 3, opStatus);  
  outbuf.setCharAt(REPLY_PAYLOAD_START + 5,END_BUFFER_MARK);
}


void prepareReplyUpdateLedMode(nodeDefinition node, outputBufferHandler outbuf){
  prepareReplyHeader(node, outbuf);
  if (node.getFlashLedMode()) {  
    outbuf.setCharAt(REPLY_PAYLOAD_START,'F');
  } else {
     outbuf.setCharAt(REPLY_PAYLOAD_START,'G');   
  } 
  outbuf.setCharAt(REPLY_PAYLOAD_START + 1,END_BUFFER_MARK);
}


int extractCheckedAddress(inputBufferHandler inbuf) {
  int startbyte;
  
  startbyte = ADDRESS_START;
  int k1 = inbuf.getHexByteAt(startbyte);
  if (k1 < 0) return -1;

  startbyte += 2;
  int k2 = 255 - inbuf.getHexByteAt(startbyte);
  if (k2 < 0) return -1;

  if (k1 != k2) return -1;
  return k1;
}


void requestNodeRegisterDescription(nodeDefinition node, inputBufferHandler inbuf, outputBufferHandler outbuf, int registerNumber){
  
}

void requestDeviceRegisterDescription(nodeDefinition node, inputBufferHandler inbuf, outputBufferHandler outbuf, int deviceNumber, int registerNumber) {
  
}
  
void requestNodeRegisterValue(nodeDefinition node, inputBufferHandler inbuf, outputBufferHandler outbuf, int registerNumber){
  
}

void requestDeviceRegisterValue(nodeDefinition node, inputBufferHandler inbuf, outputBufferHandler outbuf, int deviceNumber, int registerNumber) {
  
}

void updateNodeRegisterValue(nodeDefinition node, inputBufferHandler inbuf, outputBufferHandler outbuf, int registerNumber){
  
}

void updateDeviceRegisterValue(nodeDefinition node, inputBufferHandler inbuf, outputBufferHandler outbuf, int deviceNumber, int registerNumber) {
  
}

int setAddress(nodeDefinition node, inputBufferHandler inbuf) {
  int addr = extractCheckedAddress(inbuf);
  if (!node.validNodeAddress(addr)) return false;
  node.setNodeAddress(addr);

  return true;
  
}

void restartNode(){
  
}


void processCommand(nodeDefinition node, inputBufferHandler inbuf, outputBufferHandler outbuf, bool allowSetAddres) {

  inbuf.checkAnyMessage();

  if (! inbuf.inputCommandReady()) return;

  char msgType = inbuf.getCharAt(0);
  char cmd = inbuf.getCharAt(CMD_START); 

  if ((msgType == TYPE_SETADDRESS) && (allowSetAddres)) {
    int oldAddress = node.getNodeAddr();
    if (setAddress(node, inbuf) ) {
      prepareReplyUpdateAddress(node, outbuf, oldAddress, CMD_OK);
    } else {
      prepareReplyUpdateAddress(node, outbuf, oldAddress, ERR_CANNOT_SET_ADDRESS);
    }
    inbuf.clearBuffer();
    return;
  }

  if (msgType == TYPE_RESTART) restartNode(); // restart all  nodes from network
  
  if (msgType != TYPE_COMMAND) {
    inbuf.clearBuffer();
    return;
  }

  int targetAddress = extractCheckedAddress(inbuf);
  if (targetAddress < 0) {inbuf.clearBuffer(); return; }
  if (targetAddress != node.getNodeAddr()) {inbuf.clearBuffer(); return; }
  
  if (cmd == CMD_RESTART_NODE) restartNode();

  if ((cmd == CMD_START_FLASH_LED) || (cmd == CMD_STOP_FLASH_LED)) {
    node.setFlashLedMode((cmd == CMD_START_FLASH_LED));
    prepareReplyUpdateLedMode(node, outbuf);
    inbuf.clearBuffer();
    return;
  }

  int deviceNumber = inbuf.getHexByteAt(CMD_START+1);
  int registerNumber = inbuf.getHexByteAt(CMD_START+2);
  
  if ((cmd == CMD_GET_REGISTER_DESCRIPTION) && (deviceNumber == 0)) { requestNodeRegisterDescription(node, inbuf, outbuf, registerNumber );inbuf.clearBuffer();return;}

  if ((cmd == CMD_GET_REGISTER_DESCRIPTION) && (deviceNumber > 0)) { requestDeviceRegisterDescription(node, inbuf, outbuf, deviceNumber, registerNumber);inbuf.clearBuffer();return;}

  if ((cmd == CMD_GET_REGISTER_VALUE) && (deviceNumber == 0)) { requestNodeRegisterValue(node, inbuf, outbuf, registerNumber );inbuf.clearBuffer();return;}

  if ((cmd == CMD_GET_REGISTER_VALUE) && (deviceNumber > 0)) { requestDeviceRegisterValue(node, inbuf, outbuf, deviceNumber, registerNumber);inbuf.clearBuffer();return;}

  if ((cmd == CMD_SET_REGISTER_VALUE) && (deviceNumber == 0)) { updateNodeRegisterValue(node, inbuf, outbuf, registerNumber );inbuf.clearBuffer();return;}

  if ((cmd == CMD_SET_REGISTER_VALUE) && (deviceNumber > 0)) { updateDeviceRegisterValue(node, inbuf, outbuf, deviceNumber, registerNumber);inbuf.clearBuffer();return;}

  
}
