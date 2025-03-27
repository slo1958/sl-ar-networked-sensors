# About Worker

A worker has two modes of operations
- stand alone
- normal (networked) mode

The mode of operation is decided by the state of BUTTON_IO during restart.

## Stand Alone mode
The worker starts in stand alone if BUTTON_IO is HIGH during restart.

### Description
In stand alone mode, it expect simple commands from the hardware serial, typically from a terminal.
Those commands are used:
- to set the address of the worker (001..250)
- to request the status of the worker
- to poll the sensor (in the first version, a DS18B20 returning temperature)

### Stand alone command

 CxY

x = commands

A : update address
Format: CAyyy;
yyy is address between 001 .. 250
Example: CA123;
Set address of device to 123


P : enable/disable repeat polling of temperature
Format: Py; 
0 (off) or 1 (on)
Example P0;
Turn off repeat polling

S : show status
Format: S;
Example S;
Request worker status


## Normal (networked) mode
The worker starts in stand alone if BUTTON_IO is LOW during restart.
All communication happens in ASCII, so the number 123 is three characters.
In normal mode, the worker expect commands starting with a 'C' followed by a command and the address of the worker.
If BUTTON_IO moves to HIGH, the worker will accept a command to update its address, using the address field of the command
instead of using this field to filter the command.
