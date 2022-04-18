/* main.h is intended for declaring functions and variables shared between the
user code files. main.h also offers a variety of configuarble options for
tailoring PROS to our needs. */
#include "main.h"
// math.h is designed for basic mathematical operations
#include "math.h"

// using namespace pros reduces the length of declarations when using C++.
using namespace pros;
// using namespace standard
using namespace std;

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
ADIDigitalOut transmission(4, 0);
ADIDigitalOut claw(1, 0);
ADIDigitalOut tilterClamp(3, 0);
ADIDigitalOut tilter(2, 0);

// ring intake
Motor ringIntake(9, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

// controller
Controller master(E_CONTROLLER_MASTER);

// sensors

/* The inertial sensor is a 3-axis accelerometer and gyroscope. The
accelerometer measures linear acceleration of the robot, while the gyroscope
measures the rate of rotation about the inertial sensor 3-axis. We only use the
gyroscope. The inertial sensor is used in our move function to implement heading
correction and turn function to turn accurately. */
Imu inertial(1);

/* The optical shaft encoders measure both the position and direction of rotation
of a VEX shaft. We can calculate the speed of the shaft, as well as the distance
it has traveled. The encoders give us the ability to measure angular travel,
determine rotational direction, calculate shaft speed, calculate distance traveled,
increase navigational control, and ultimately more autonomous functionality. */
ADIEncoder rEncoder(5, 6, false);
ADIEncoder lEncoder(7, 8, true);

/* Runs initialization code. This occurs as soon as the program is started. All
other competition modes are blocked by initialize. */
void initialize() {

	pros::lcd::initialize();
	pros::lcd::print(5, "Hello PROS User!");

	// 5 second delay that allows for inertial sensor to reset
	// inertial.reset(); // calibrates IMU

	// delay(5000);


	// base
	l1.set_brake_mode(MOTOR_BRAKE_COAST);
	l2.set_brake_mode(MOTOR_BRAKE_COAST);
	l3.set_brake_mode(MOTOR_BRAKE_COAST);
	r1.set_brake_mode(MOTOR_BRAKE_COAST);
	r2.set_brake_mode(MOTOR_BRAKE_COAST);
	r3.set_brake_mode(MOTOR_BRAKE_COAST);

	// enable brake mode for the lift motor
	lift.set_brake_mode(MOTOR_BRAKE_BRAKE);

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
	pros::lcd::print(2, "hi");
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
	pros::lcd::print(3, "hi");

	while (true) {

		drive();
	 // driveRingIntake();
		driveLift();
		driveClaw();
		driveTilter();
		driveTransmission();
		// pros::lcd::print(1, "l: %f, r: %f, a: %f", lEncoder.get_value(), rEncoder.get_value(), inertial.get_heading());
	}
}
