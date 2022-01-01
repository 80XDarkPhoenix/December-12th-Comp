#include "main.h"

#include "math.h"

using namespace pros;

/* "Arcade" control for base. One joystick is used to control
the base. The Y axis controls forward and backward motion and the X axis
controls turning motion. Function gets analog of joystick and "sends" them to
the base motors.*/
void drive() {
	/* "get_analog" gets the value of the analog channel (joystick) on the
	controller */
	float drives = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
	float turns = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

	// "move" sets the voltage for the motor from -127 to 127
	fr.move(drives - turns);
	br.move(drives - turns);
	br2.move(drives - turns);
	fl.move(drives + turns);
	bl.move(drives + turns);
	bl2.move(drives + turns);
}

// Moves the front lift up and down.
void driveFrontLift() {
	/* "get_digital" checks if a digital channel "button" on the controller is
	currently pressed */
	// "move" sets the voltage for the motor from -127 to 127
	if(master.get_digital(DIGITAL_R1)==1) {
		frontLift.move(127);
	}
	else if(master.get_digital(DIGITAL_R2)) {
		frontLift.move(-127);
	}
	else
	{
		frontLift.move(0);
	}
}

// Moves the front claw up and down.
void drivefrontClaw() {
	//  0 and 1 are states of the pnuematics.
	if(master.get_digital(DIGITAL_X)==1) {
		frontClaw.set_value(0);
	}
	else if(master.get_digital(DIGITAL_Y))
	frontClaw.set_value(1);
}

// Moves the front claw up and down.
void driveBackClaw() {
	//  0 and 1 are states of the pnuematics.
	if(master.get_digital(DIGITAL_A)==1) {
		backClaw.set_value(0);
	}
	else if(master.get_digital(DIGITAL_B))
	backClaw.set_value(1);
}

// Moves ring conveyor.
void driveRingIntake() {
	if(master.get_digital(DIGITAL_L1)==1) {
		ringIntake.move(50);
	}
	else if(master.get_digital(DIGITAL_L2)) {
		ringIntake.move(-50);
	}
	else
	{
		ringIntake.move(0);
	}
}
