#include "main.h"
#include "math.h"

using namespace pros;

/* "move" sets the voltage for the motor from -127 to 127. It is used throughout
the code, especially opcontrol. */

/* "get_digital" checks if a digital channel "button" on the controller is
currently pressed. */

// All the buttons/joysticks used are chosen based off the driver's preference.

/* "Arcade" control for base. One joystick is used to control
the base. The Y axis controls forward and backward motion and the X axis
controls turning motion. Function gets analog of joystick and "sends" them to
the base motors.*/
void drive() {
	// "get_analog" gets the value of an analog channel (joystick) on a controller
	float drives = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
	float turns = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

	fr.move(drives - turns);
	br.move(drives - turns);
	br2.move(drives - turns);
	fl.move(drives + turns);
	bl.move(drives + turns);
	bl2.move(drives + turns);
}

// moves the front lift up and down
void driveFrontLift() {
	if(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > 5) {
		frontLift.move(127);
	}
	else if(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < -5) {
		frontLift.move(-127);
	}
	else
	{
		frontLift.move(0);
	}
}

// Claws
//  0 and 1 are states of the pnuematics.

// moves the front claw up and down
void driveFrontClaw() {
	if(master.get_digital(DIGITAL_R1) == 1) {
		frontClaw.set_value(0);
	}
	else if(master.get_digital(DIGITAL_R2))
	frontClaw.set_value(1);
}

// moves the back claw up and down
void driveBackClaw() {
	if(master.get_digital(DIGITAL_L1) == 1) {
		backClaw.set_value(1);
		backClaw2.set_value(0);
	}
	else if(master.get_digital(DIGITAL_L2))
		backClaw.set_value(0);
		backClaw2.set_value(1);
}

// moves the ring intake
void driveRingIntake() {
	if(master.get_digital(DIGITAL_A) == 1) {
		ringIntake.move(-100);
	}
	else
	{
		ringIntake.move(100);
	}
}
