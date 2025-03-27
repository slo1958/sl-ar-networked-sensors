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

 Cxy

x = commands<br>
y = parameter<br>

A : update address<br>
Format: CAyyy;<br>
yyy is address between 001 .. 250<br>
Example: CA123;<br>
Set address of device to 123<br>

P : enable/disable repeat polling of temperature<br>
Format: CPy; <br>
y is 0 (off) or 1 (on)<br>
Example CP0;<br>
Turn off repeat polling<br>

S : show status<br>
Format: CS;<br>
Example CS;<br>
Request worker status<br>


## Normal (networked) mode
The worker starts in stand alone if BUTTON_IO is LOW during restart.

### Description
All communication happens in ASCII, so the number 123 is three characters.
In normal mode, the worker expect commands starting with a 'C' followed by a command and the address of the worker.
If BUTTON_IO moves to HIGH, the worker will accept a command to update its address, using the address field of the command
instead of using this field to filter the command.

