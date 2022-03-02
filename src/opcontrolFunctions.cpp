#include "main.h"
#include "math.h"

using namespace pros;

// All the buttons/joysticks used are chosen based off the driver's preference.

// BASE

// moves the base
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

// LIFT

// moves the front lift using buttons R1 and R2
void driveFrontLift() {
	if(master.get_digital(DIGITAL_R1)) {
		// move lift up
		frontLift.move(127);
	}
	else if(master.get_digital(DIGITAL_R2)) {
		// move lift down
		frontLift.move(-127);
	}
	else
	{
		frontLift.move(0);
	}
}

// CLAWS

// moves the front claw using buttons X and Y
void driveFrontClaw() {
	if(master.get_digital(DIGITAL_X) == 1) {
		// lifts front claw
		frontClaw.set_value(1);
	}
	else if(master.get_digital(DIGITAL_Y))
		// hooks front claw
		frontClaw.set_value(0);
}

// moves the back claw using buttons L1 and L2
void driveBackClaw() {
	if(master.get_digital(DIGITAL_L1) == 1) {
		// hooks back claw
		backClaw.set_value(0);
	}
	else if(master.get_digital(DIGITAL_L2))
		// lifts back claw
		backClaw.set_value(1);
}

// moves the ring intake using button A
void driveRingIntake() {
	if(master.get_digital(DIGITAL_A) == 1) {
		// outtakes ring intake
		ringIntake.move(-127);
	}
	else
	{
		// runs ring intake unless A is pressed
		ringIntake.move(127);
	}
}
