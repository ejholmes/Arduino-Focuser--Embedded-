README
======
- This project is the embedded code on the Arduino board for the Arduino focuser. 
- It uses the [AFMotor library](http://www.ladyada.net/make/mshield/use.html) and a modified Messenger library.
- Code is for the motor shield from [adafruit industries](http://adafruit.com/index.php?main_page=product_info&cPath=17_21&products_id=81).


What is it?
-------------
The purpose of this project is to provide a layer between the hardware and [ASCOM driver](http://github.com/ejholmes/Arduino-Focuser--ASCOM-Driver-) for issuing move commands for a stepper motor, in my case it is the stepper motor for my homemade telescope focuser. This is accomplished by parsing Serial commands sent from the ASCOM Driver. When a command is received in the ": COMMAND <ARGUMENT> #" format, the Messenger object is passed to the Focuser::interpretCommand() function, which looks at the COMMAND and acts accordingly.
 
The following commands are currently available:

- ": M 100 #" Moves the focuser to position 100.
- ": L #" Issues a motor.release(). Some steppers get pretty hot when the coils are not released.
- ": R <0-1> #" Reverses motor direction. 0=false, 1=true.
- ": P 1523 #" Sets the current position to 1523. Note, this does not issue a move, it just tells the focuser that it's at said position.
- ": G #" Prints out the current position to the serial port. Useful for syncing.
- ": H #" Doesn't really do anything since anything in the serial buffer will halt the motor. Just prettier.