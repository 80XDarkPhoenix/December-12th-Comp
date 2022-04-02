#include "main.h"
#include "math.h"

/* All the buttons/joysticks used are chosen based off the driver's preference.
Throughout */

// BASE

// moves the base
void drive() {
	float drives = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
	float turns = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

	r1.move(drives - turns);
	l1.move(drives + turns);
	r2.move(drives - turns);
	l2.move(drives + turns);
	r3.move(drives - turns);
	l3.move(drives + turns);
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
	if(master.get_digital(DIGITAL_X)) {
		// lifts front claw
		frontClaw.set_value(1);
	}
	else if(master.get_digital(DIGITAL_Y))
		// hooks front claw
		frontClaw.set_value(0);
}

// moves the back claw using buttons L1 and L2
void driveBackClaw() {
	if(master.get_digital(DIGITAL_L1)) {
		// hooks back claw
		backClaw.set_value(0);
	}
	else if(master.get_digital(DIGITAL_L2))
		// lifts back claw
		backClaw.set_value(1);
}

// moves the ring intake using button A
void driveRingIntake() {
	if(master.get_digital(DIGITAL_A)) {
		// outtakes ring intake
		ringIntake.move(-127);
	}
	else
	{
		// runs ring intake unless A is pressed
		ringIntake.move(127);
	}
}

void op() {
	drive();
	driveFrontLift();
	driveFrontClaw();
	driveBackClaw();
	driveRingIntake();
	delay(20);
}
