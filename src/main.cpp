#include "main.h"
#include "math.h"

using namespace pros;

Motor fr(, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // front right
Motor fl(, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // front left
Motor br(, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // back right
Motor bl(, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // back left

Motor frontLift(, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor backLift(, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor lever(, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Controller master(E_CONTROLLER_MASTER); // base, Srihith
Controller partner(E_CONTROLLER_PARTNER); // lifts, Kriya

/* Runs initialization code. This occurs as soon as the program is started. All
other competition modes are blocked by initialize; it is recommended to keep
execution time for this mode under a few seconds. */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

/* Runs while the robot is in the disabled state of Field Management System or
the VEX Competition Switch, following either autonomous or opcontrol. When the
robot is enabled, this task will exit. */
void disabled() {}

/* Runs after initialize(), and before autonomous when connected to the Field
Management System or the VEX Competition Switch. This is intended for
competition-specific initialization routines, such as an autonomous selector on
the LCD.This task will exit when the robot is enabled and autonomous or
opcontrol starts. */
void competition_initialize() {}

/* Runs the user autonomous code. This function will be started in its own task
with the default priority and stack size whenever the robot is enabled via the
Field Management System or the VEX Competition Switch in the autonomous mode.
Alternatively, this function may be called in initialize or opcontrol for
non-competition testing purposes. If the robot is disabled or communications is
lost, the autonomous task will be stopped. Re-enabling the robot will restart
the task, not re-start it from where it left off. */
void autonomous() {}

// opcontrol functions

/* Master driver's "arcade" control for base. One joystick is used to control
the base. The Y axis controls forward and backward motion and the X axis
controls turning motion. Function gets analog of joystick and "sends" them to
the base motors.*/
void drive() {
float drives = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
float turns = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

  fr.move(drives - turns);
  fl.move(drives + turns);
  br.move(drives - turns);
  bl.move(drives + turns);
}

void driveFrontLift() {
  if(partner.get_digital(DIGITAL_R1)==1) {
    frontLift.move(127);
  }
  else if(partner.get_digital(DIGITAL_R2))
    frontLift.move(-127);
}

void driveLever() {
	if(partner.get_digital(DIGITAL_A)==1) {
		lever.move(127);
	}
	else if(partner.get_digital(DIGITAL_B))
		lever.move(-127);
}

void driveBackLift() {
  if(partner.get_digital(DIGITAL_L1)==1) {
    backLift.move(127);
  }
  else if(partner.get_digital(DIGITAL_L2))
    backLift.move(-127);
}

/* Runs the operator control code. This function will be started in its own task
with the default priority and stack size whenever the robot is enabled via the
Field Management System or the VEX Competition Switch in the operator control
mode. If no competition control is connected, this function will run immediately
following initialize(). If the robot is disabled or communications is lost, the
operator control task will be stopped. Re-enabling the robot will restart the
task, not resume it from where it left off. */
void opcontrol() {
	while (true) {
		drive();
		driveFrontLift();
		driveLever();
		driveBackLift();
		delay(20);
	}
}

// autonomous functions

void move() {}

void turn() {}

void liftFront() {
	frontLift.move(127);
}

void lowerFront() {
	frontLift.move(-127);
}

void liftLever() {
	lever.move(127);
}

void lowerLever() {
	lever.move(-127);
}

void liftBack() {
	backLift.move(127);
}

void lowerBack() {
	backLift.move(-127);
}

// fifteen second autonomous

// skills autonomous
