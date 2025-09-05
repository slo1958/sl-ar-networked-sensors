#include "customNode.h"
 

//
// Custom node
//
// Building the node
//

// 
OneWire oneWire(ONE_WIRE_BUS_IO);
DallasTemperature sensors(&oneWire);
DeviceAddress SensorAddress;


customNodeDefinition::customNodeDefinition(){
  // Init the parent node
  nodeDefinition();

  myDevice1.sensors = sensors;
  myDevice1.sensorID = 0;

  myDevice2.sensors = sensors;
  myDevice2.sensorID = 1;
  

  
  strcpy(nodeName, "DallasTemp");
  strcpy(nodeModel, "1");

  _lastDeviceID = LAST_DEVICE_ID;
  
  // Add code to init the node
  
}
void customNodeDefinition::configureCustomNode(){
  sensors.begin();

  SensorCount = sensors.getDeviceCount();

  SensorParasitePower = sensors.isParasitePowerMode();
  SensorDeviceFound = sensors.getAddress(SensorAddress, 0);

  nodeDefinition::configureCommonNode();
}

deviceDefinition* customNodeDefinition::getDevice(int deviceNumber){
  switch (deviceNumber) {
    case MYDEVICE_1:
      return &myDevice1;
    case MYDEVICE_2:
      return &myDevice2;
    default:
       return nodeDefinition::getDevice(deviceNumber);
  } 
}

 
