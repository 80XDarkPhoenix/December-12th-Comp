/* "main.h", is intended for declaring functions and variables shared between
the user code files. main.h offers a variety of configurable options for
tailoring PROS to our needs. */
#include "main.h"

// "math.h", is designed for basic mathematical operations.
#include "math.h"

// using namespace pros reduces the length of declarations.
using namespace pros;

// INITIALIZATION

// Base
Motor fr(, E_MOTOR_GEARSET_18, , E_MOTOR_ENCODER_DEGREES); // front right
Motor br(, E_MOTOR_GEARSET_18, , E_MOTOR_ENCODER_DEGREES); // back right
Motor br2(, E_MOTOR_GEARSET_18, , E_MOTOR_ENCODER_DEGREES); // elevated back right
Motor fl(, E_MOTOR_GEARSET_18, , E_MOTOR_ENCODER_DEGREES); // front left
Motor bl(, E_MOTOR_GEARSET_18, , E_MOTOR_ENCODER_DEGREES); // back left
Motor bl2(, E_MOTOR_GEARSET_18, , E_MOTOR_ENCODER_DEGREES); // elevated back left

// Lift
Motor frontLift(, E_MOTOR_GEARSET_18, , E_MOTOR_ENCODER_DEGREES);

// Claws
/* The claws is pnuematic, so they are connected to the brain through ADI ports,
therefore it is initialized as an "ADIDIgitalOut". The second parameter is the
state of the pneumatics. */
ADIDigitalOut frontClaw(, );
ADIDigitalOut backClaw(, );

// Ring Intake
Motor ringIntake(, E_MOTOR_GEARSET_18, , E_MOTOR_ENCODER_DEGREES);

// Controllers
Controller master(E_CONTROLLER_MASTER);
// Sensor
/* The inertial sensor is a 3-axis accelerometer and gyroscope. The
accelerometer measures linear acceleration of the robot, while the gyroscope
measures the rate of rotation about the inertial sensor 3-axis. The inertial
sensor helps us have accurate turns. When we were testing our turns, we
discovered that they were not accurate. We decided to use the inertial sensor to
help with this. */
Imu inertial(18);

/* Runs initialization code. This occurs as soon as the program is started. All
other competition modes are blocked by initialize. */
void initialize() {
	inertial.reset();
	delay(3000); // allows for inertial sensor to reset
	lcd::initialize();

	lcd::print(1, "IMU heading: %3f", getAngle); // prints angle on LCD screen

	// Base
	fl.set_brake_mode(MOTOR_BRAKE_BRAKE);
	bl.set_brake_mode(MOTOR_BRAKE_BRAKE);
	bl2.set_brake_mode(MOTOR_BRAKE_BRAKE);
	fr.set_brake_mode(MOTOR_BRAKE_BRAKE);
	br.set_brake_mode(MOTOR_BRAKE_BRAKE);
	br2.set_brake_mode(MOTOR_BRAKE_BRAKE);

	fl.set_current_limit(11500);
	bl.set_current_limit(11500);
	bl2.set_current_limit(11500);
	fr.set_current_limit(11500);
	br.set_current_limit(11500);
	br2.set_current_limit(11500);

	fl.set_voltage_limit(11500);
	bl.set_voltage_limit(11500);
	bl2.set_voltage_limit(11500);
	fr.set_voltage_limit(11500);
	br.set_voltage_limit(11500);
	br2.set_voltage_limit(11500);

	// Lift
	frontLift.set_brake_mode(MOTOR_BRAKE_BRAKE);

	// Ring Intake
	ringIntake.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/* Runs while the robot is in the disabled state of Field Management System or
the VEX Competition Switch, following either autonomous or opcontrol. When the
robot is enabled, this task will exit. */
void disabled() {}

/* Runs after initialize(), and before autonomous when connected to the Field
Management System or the VEX Competition Switch. This is intended for
competition-specific initialization routines, such as an autonomous selector on
the LCD. This task will exit when the robot is enabled and autonomous or
opcontrol starts. */
void competition_initialize() {}

/* Runs the user autonomous code. This function will be started in its own task
with the default priority and stack size whenever the robot is enabled via the
Field Management System or the VEX Competition Switch in the autonomous mode.
Alternatively, this function may be called in initialize or opcontrol for
non-competition testing purposes. If the robot is disabled or communications is
lost, the autonomous task will be stopped. Re-enabling the robot will restart
the task, not re-start it from where it left off. */
void autonomous() {
}

/* Runs the operator control code. This function will be started in its own
task with the default priority and stack size whenever the robot is enabled
via the Field Management System or the VEX Competition Switch in the
operator control mode. If no competition control is connected, this function
will run immediately following initialize(). If the robot is disabled or
communications is lost, the operator control task will be stopped.
Re-enabling the robot will restart the task, not resume it from where it
left off. */
void opcontrol() {
	while (true) {
		drive();
		driveFrontLift();
		driveFrontClaw();
		driveBackClaw();
		driveRingIntake();
		delay(20);
	}
}
