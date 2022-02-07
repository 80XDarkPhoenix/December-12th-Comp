#include "main.h"
#include "math.h"

using namespace pros;

// INITIALIZATION

// base
Motor fr(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // front right
Motor br(16, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // back right
Motor br2(7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // elevated back right
Motor fl(14, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // front left
Motor bl(18, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // back left
Motor bl2(8, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // elevated back left

// lift
Motor frontLift(15, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

// claws
/* The claws are pnuematic, so they are connected to the brain through ADI ports,
therefore it is initialized as an "ADIDIgitalOut". The second parameter is the
state of the pneumatics. */
ADIDigitalOut frontClaw(2, 1);
ADIDigitalOut backClaw(1, 1);
ADIDigitalOut backClaw2(3, 1);

// ring intake
Motor ringIntake(21, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

// Controllers
Controller master(E_CONTROLLER_MASTER);

// Sensors

/* The inertial sensor is a 3-axis accelerometer and gyroscope. The
accelerometer measures linear acceleration of the robot, while the gyroscope
measures the rate of rotation about the inertial sensor 3-axis. The inertial
sensor helps us have accurate turns. When we were testing our turns, we
discovered that they were not accurate. We decided to use the inertial sensor to
help with this. */
Imu inertial(12);

/* The V5 Distance Sensor measures distance to an object, approximate object
size, and approach speed. The distance measurement range is 20mm to 2,000mm.
The V5 Distance Sensor uses a classroom safe Class 1 Laser, similar to those
used on modern cell phones for head detection. The laser allows the sensor to
have a very narrow field of view, so detection is always directly in front of
the sensor. We use the distance sensor to detect the wall, so our autonomous
stays consistent on multiple fields and in different conditions. */
//Distance frontDistance();
//Distance backDistance();

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

	// lift
	frontLift.set_brake_mode(MOTOR_BRAKE_BRAKE);

	// ring Intake
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
	//rightMobileGoalAllianceGoal();
	// rightMobileGoalCenterGoalAllianceGoal();
  // leftMobileGoalAllianceGoal();
	// skillsAuton();
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
