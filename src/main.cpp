/* main. is intended for decalring functions and variables shared between the user code files.
main.h also offers a variety of configuarble options for tailoring PROS to our needs. */
#include "main.h"
#include "math.h"

// using namespace pros reduces the length of declarations when using C++.
using namespace pros;

// INITIALIZATION

// base
Motor fr(4, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES); // front right
Motor br(2, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES); // back right
Motor br2(3, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES); // elevated back right

Motor fl(7, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES); // front left
Motor bl(9, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES); // back left
Motor bl2(8, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES); // elevated back left

// lift
Motor frontLift(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

// claws
/* The claws are pnuematic, so they are connected to the brain through ADI ports,
therefore they is initialized as an "ADIDIgitalOut". The second parameter is the
state of the pneumatics. */
ADIDigitalOut frontClaw(3, 1);
ADIDigitalOut backClaw(1, 1);

// ring intake
Motor ringIntake(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

// controller
Controller master(E_CONTROLLER_MASTER);

// sensor

/* The inertial sensor is a 3-axis accelerometer and gyroscope. The
accelerometer measures linear acceleration of the robot, while the gyroscope
measures the rate of rotation about the inertial sensor 3-axis. We only use the
gyroscope. The inertial sensor is used in our move function to implement heading
correction and turn function to turn accurately. */
Imu inertial(21);

/* Runs initialization code. This occurs as soon as the program is started. All
other competition modes are blocked by initialize. */
void initialize() {
	inertial.reset(); // calibrates IMU
	// 5 second delay that allows for inertial sensor to reset
	delay(5000);
	lcd::initialize();

	// prints angle on LCD screen
	lcd::print(1, "IMU heading: %3f", getAngle);

	// base
	/* The base is set to brake mode per the drivers preference and so it is easier
	for the robot to climb the bridge. */
	fl.set_brake_mode(MOTOR_BRAKE_BRAKE);
	bl.set_brake_mode(MOTOR_BRAKE_BRAKE);
	bl2.set_brake_mode(MOTOR_BRAKE_BRAKE);
	fr.set_brake_mode(MOTOR_BRAKE_BRAKE);
	br.set_brake_mode(MOTOR_BRAKE_BRAKE);
	br2.set_brake_mode(MOTOR_BRAKE_BRAKE);

	// enable brake mode for the lift motor
	frontLift.set_brake_mode(MOTOR_BRAKE_BRAKE);

	// enable brake mode for the ring intake motor
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
	skills();
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
