*This project is the embedded code on the Arduino board for the Arduino focuser. 
*It uses the AFMotor library (http://www.ladyada.net/make/mshield/use.html) and a modified Messenger library.

*You must use a motor shield from adafruit industries (http://adafruit.com/index.php?main_page=product_info&cPath=17_21&products_id=81) to use this source code.


WHAT IS IT?
-------------
The purpose of this project is to provide a layer between the hardware and ASCOM driver for issuing move commands for a stepper motor, in my case it is the stepper motor for my homemade telescope focuser. This is accomplished by parsing Serial commands sent from the ASCOM Driver. When a command is received in the ": COMMAND <ARGUMENT> #" format, the Messengerobject is passed to the Focuser::interpretCommand() function, which looks at the COMMAND and acts accordingly.
 
The following commands are currently available:

": M <POSITION> #" Moves the focuser to <POSITION>.
": R #" Issues a motor.release(). Some steppers get pretty hot when the coils are not released.
": P #" Sets the current position;
": G #" Prints out the current position to the serial port. Useful for syncing.
": H #" Doesn't really do anything since anything in the serial buffer will halt the motor. Just prettier.