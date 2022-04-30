/* main.cpp includes the initialization of the different parts of the robot,
including sensors. It also contains the necessary preset initialize, disabled,
competition_initialize, autonomous, and opcontrol functions. */

/* main.h is intended for declaring functions and variables shared between the
user code files. main.h also offers a variety of configuarble options for
tailoring PROS to our needs. */
#include "main.h"
#include "math.h" // math.h is designed for basic mathematical operations

// using namespace pros reduces the length of declarations when using C++.
using namespace pros;
using namespace std; // using namespace standard

// INITIALIZATION

// base
Motor r1(21, E_MOTOR_GEARSET_06,true, E_MOTOR_ENCODER_DEGREES); // 1st right
Motor r2(18, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES); // 2nd right
Motor r3(7, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES); // 3rd right

Motor l1(13, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES); // 1st left
Motor l2(3, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES); // 2nd left
Motor l3(2, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES); // 3rd left

// lift
Motor lift(16, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);

// claws
/* The claws are pnuematic, so they are connected to the brain through ADI ports,
therefore they is initialized as an "ADIDIgitalOut". The second parameter is the
state of the pneumatics. */

// The base transmission is preset to 1, speed mode.
ADIDigitalOut transmission(4, 1);
// The claw is preset to starts down, or else the robot is not in 18 inches.
ADIDigitalOut claw(6, 0);
// There are 2 parts of the back claw, the clamp and the tilter.
// The clamp is preset to starts up.
ADIDigitalOut tilterClamp(5, 1);
// The tilter is preset to start tilted so the robot stays in 18 inches.
ADIDigitalOut tilter(3, 1);
ADIDigitalOut highRing(2, 0);

// ring intake
Motor ringIntake(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

// controller
Controller master(E_CONTROLLER_MASTER);

// sensors

/* The inertial sensor is a 3-axis accelerometer and gyroscope. The
accelerometer measures linear acceleration of the robot, while the gyroscope
measures the rate of rotation about the inertial sensor 3-axis. We rant into
issues while testing our move method with the robot moving in a straight line.
When the robot would move at angle, it would be at the wrong place to pick up
goals and cause inaccuracies elsewhere. We implemented the inertial sensor to
detect when the robot is not at the correct angle, and to turn slightly while
moving, also known as heading correction. Our turn function was originally based
off the inertial sensor just to correct the angle, but now the whole function
is based off the heading the sensor gets. We are now able to turn accurately. */
Imu inertial(1);

/* The optical shaft encoders measure both the position and direction of
rotation of a VEX shaft. We can calculate the speed of the shaft, as well as the
distance it has traveled. The encoders give us the ability to measure angular
travel, determine rotational direction, calculate shaft speed, calculate
distance traveled, increase navigational control, and ultimately more autonomous
functionality. The encoder wheels are used it our move function instead of our
motor encoders in case they skip, which has happened in the past. */
ADIEncoder rEncoder({14, 1, 2}, false);
ADIEncoder lEncoder({14, 3, 4}, true);

/* Runs initialization code. This occurs as soon as the program is started. All
other competition modes are blocked by initialize. */
void initialize() {

	inertial.reset(); // reset() calibrates the IMU
	/* Calibration takes approximately 2 seconds
	reset() does not block that long */
	delay(5000); // 5 second delay for IMU to calibrate

	pros::lcd::initialize(); // initializes the LCD screen on the brain
	pros::lcd::print(1, "Initialize");

	transmission.set_value(1);

	// reset() sets the encoder valye to zero
	rEncoder.reset();
	lEncoder.reset();

  // base
	l1.set_brake_mode(MOTOR_BRAKE_BRAKE);
	l2.set_brake_mode(MOTOR_BRAKE_BRAKE);
	l3.set_brake_mode(MOTOR_BRAKE_BRAKE);
	r1.set_brake_mode(MOTOR_BRAKE_BRAKE);
	r2.set_brake_mode(MOTOR_BRAKE_BRAKE);
	r3.set_brake_mode(MOTOR_BRAKE_BRAKE);

	// lift
	lift.set_brake_mode(MOTOR_BRAKE_BRAKE);

	// ring intake
	ringIntake.set_brake_mode(MOTOR_BRAKE_BRAKE);

} // end of initialize

/* Runs while the robot is in the disabled state of Field Management System or
the VEX Competition Switch, following either autonomous or opcontrol. When the
robot is enabled, this task will exit. */
void disabled() {} // end of disabled

/* Runs after initialize(), and before autonomous when connected to the Field
Management System or the VEX Competition Switch. This is intended for
competition-specific initialization routines, such as an autonomous selector on
the LCD. This task will exit when the robot is enabled and autonomous or
opcontrol starts. */
void competition_initialize() {} // end of competition_initialize

// AUTONOMOUS

/* Runs the user autonomous code. This function will be started in its own task
with the default priority and stack size whenever the robot is enabled via the
Field Management System or the VEX Competition Switch in the autonomous mode.
Alternatively, this function may be called in initialize or opcontrol for
non-competition testing purposes. If the robot is disabled or communications is
lost, the autonomous task will be stopped. Re-enabling the robot will restart
the task, not re-start it from where it left off. */
void autonomous() {
	pros::lcd::print(3, "autonomous0");
	rMobile1();
} // end of autonomous

// OPCONTROL

/* Runs the operator control code. This function will be started in its own
task with the default priority and stack size whenever the robot is enabled
via the Field Management System or the VEX Competition Switch in the
operator control mode. If no competition control is connected, this function
will run immediately following initialize(). If the robot is disabled or
communications is lost, the operator control task will be stopped.
Re-enabling the robot will restart the task, not resume it from where it
left off. */
void opcontrol() {

	// The base motors are set to coast per the driver's preference.
	l1.set_brake_mode(MOTOR_BRAKE_COAST);
	l2.set_brake_mode(MOTOR_BRAKE_COAST);
	l3.set_brake_mode(MOTOR_BRAKE_COAST);
	r1.set_brake_mode(MOTOR_BRAKE_COAST);
	r2.set_brake_mode(MOTOR_BRAKE_COAST);
	r3.set_brake_mode(MOTOR_BRAKE_COAST);

	while (true) {
		pros::lcd::print(3, "r: %d", rEncoder.get_value());
		pros::lcd::print(4, "l: %d", lEncoder.get_value());
		drive();
		driveTransmission();
	 	driveRingIntake();
		driveLift();
		driveClaw();
		driveTilter();
		delay(10);
	} // end of while loop
} // end of opcontrol
