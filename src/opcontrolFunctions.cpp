#include "main.h"
#include "math.h"

/* All the buttons/joysticks used are chosen based off the driver, Srihith's,
preference. */

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
void driveLift() {
	if(master.get_digital(DIGITAL_R1)) {
		// move lift up
		lift.move(127);
	}
	else if(master.get_digital(DIGITAL_R2)) {
		// move lift down
		lift.move(-127);
	}
	else
	{
		lift.move(0);
	}
}

// CLAWS

// moves the front claw using buttons X and Y
void driveClaw() {
	if(master.get_digital_new_press(DIGITAL_L1)) {
		// lifts front claw
		claw.set_value(1);
	}
	else if(master.get_digital_new_press(DIGITAL_L2))
	{
		// hooks front claw
		claw.set_value(0);
	}
}

void driveTransmission(){
	if(master.get_digital_new_press(DIGITAL_RIGHT)) {
		// lifts front claw
		transmission.set_value(1);
	}
	else if(master.get_digital_new_press(DIGITAL_DOWN))
		// hooks front claw
		transmission.set_value(0);
}

void driveTilter() {
	if(master.get_digital_new_press(DIGITAL_Y)) {
		// tilts the goal back
		tilterClamp.set_value(1);
	  delay(250);
		tilter.set_value(1);
	}
	else if(master.get_digital_new_press(DIGITAL_X))
	{
		tilter.set_value(0);
		delay(250);
	  tilterClamp.set_value(0);
	}
}

// moves the ring intake using button A
void driveRingIntake() {
	if(master.get_digital(DIGITAL_A)) {
		// outtakes ring intake
		ringIntake.move(-80);
	}
	else
	{
		// runs ring intake unless A is pressed
		// This speed was decided through testing.
		ringIntake.move(127);
	}
}
