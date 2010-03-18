*This project is the embedded code on the Arduino board for the Arduino focuser. 
*It uses the AFMotor library (http://www.ladyada.net/make/mshield/use.html) and a modified Messenger library.

*You must use a motor shield from adafruit industries (http://adafruit.com/index.php?main_page=product_info&cPath=17_21&products_id=81)
to use this source code.


WHAT IS IT?
-------------
The purpose of this project is to provide a layer between the hardware and ASCOM driver for issuing move commands for a stepper motor, in my case
it is the stepper motor for my homemade telescope focuser. This is accomplished by parsing Serial commands sent from the ASCOM Driver. 
When a command is received in the ": COMMAND <ARGUMENT> #" format, the Messengerobject is passed to the Focuser::interpretCommand() function,
 which looks at the COMMAND and acts accordingly.
 
The following commands are currently available:

": M <STEPS> #" Move the focuser <STEPS> steps. A negative value moves the focuser in the opposite direction.
": S <RPM> #" Sets the RPM for the AFMotor library. A larger value will move the focuser faster. 10 is a good starting value.
": R #" Issues a motor.release(). Some steppers get pretty hot when the coils are not released.
": T <STEPTYPE> #" Changes the step type to be used during move commands. The following values are available.
	1 = SINGLE
	2 = DOUBLE
	3 = INTERLEAVE
	8 = MICROSTEP
	
	These are defined in AFMotor.h