#include "main.h"
#include "math.h"

using namespace pros;

// All the buttons/joysticks used are chosen based off the driver's preference.

/* "move" sets the voltage for the motor from -127 to 127. It is used throughout
the code, especially opcontrol. */

/* "get_digital" checks if a digital channel "button" on the controller is
currently pressed. */

// "get_analog" gets the value of an analog channel (joystick) on a controller

// moves the base using left and right joysticks
void drive() {
	float drives = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
	float turns = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

	fr.move(drives - turns);
	fl.move(drives + turns);
	br.move(drives - turns);
	bl.move(drives + turns);
	br2.move(drives - turns);
	bl2.move(drives + turns);
}

// moves the front lift using buttons R1 and R2
void driveFrontLift() {
	if(master.get_digital(DIGITAL_R1)) {
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

// Claws

// moves the front claw up and down using buttons X and Y
void driveFrontClaw() {
	if(master.get_digital(DIGITAL_X) == 1) {
		frontClaw.set_value(0);
	}
	else if(master.get_digital(DIGITAL_Y))
	frontClaw.set_value(1);
}

// moves the back claw up and down using buttons L1 and L2
void driveBackClaw() {
	if(master.get_digital(DIGITAL_L1) == 1) {
		backClaw.set_value(1);
		backClaw2.set_value(0);
	}
	else if(master.get_digital(DIGITAL_L2))
		backClaw.set_value(0);
		backClaw2.set_value(1);
}

// moves the ring intake using button A
void driveRingIntake() {
	if(master.get_digital(DIGITAL_A) == 1) {
		ringIntake.move(-);
	}
	else
	{
		ringIntake.move();
	}
}
