/* main.h, is intended for declaring functions and variables shared between the
user code files. main.h offers a variety of configurable options for
tailoring PROS to our needs. */
#include "main.h"

// math.h, is designed for basic mathematical operations.
#include "math.h"

// "using namespace pros" reduces the length of declarations.
using namespace pros;

// DECLARING MOTORS, SENSOR, and CONTROLLERS

// Base
Motor fr(8, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // front right
Motor fl(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // front left
Motor br(21, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // back right
Motor bl(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // back left

// Lifts
Motor frontLift(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor backLift(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

// Claw
/* The claw uses pnuematics, so it is connected to the brain using the ADI ports
, therefore it is declared as an "ADIDIgitalOut". The second number, 0, states
the state of the pnuematics. 0 is no air, and 1 is air. */
ADIDigitalOut claw(1, 0); // change

// Controllers
/* Instead of having one person control the whole robot, we use partner
controls. The master controller is used by Srihith and controls the robot's
base. The partner controller is used by Kriya and controls the robot's front and
back lift's and lever. */
Controller master(E_CONTROLLER_MASTER); // base - Srihith
Controller partner(E_CONTROLLER_PARTNER); // lifts, lever - Kriya

// Sensor
/* The inertial sensor is a 3-axis accelerometer and gyroscope. The
accelerometer measures linear acceleration of the robot, while the gyroscope
measures the rate of rotation about the inertial sensor 3-axis.*/
Imu inertial(4);

// INITIALIZATION

/* Runs initialization code. This occurs as soon as the program is started. All
other competition modes are blocked by initialize. */
void initialize() {
	inertial.reset();
	delay(5000); // allows for inertial sensor to reset
	lcd::initialize();

	lcd::print(1, "IMU heading: %3f", getAngle); // shows angle on LCD screen

	// INITIALIZE MOTORS

	// Base
	fl.set_brake_mode(MOTOR_BRAKE_BRAKE);
	fr.set_brake_mode(MOTOR_BRAKE_BRAKE);
	bl.set_brake_mode(MOTOR_BRAKE_BRAKE);
	br.set_brake_mode(MOTOR_BRAKE_BRAKE);

	fl.set_current_limit(11500);
	fr.set_current_limit(11500);
	bl.set_current_limit(11500);
	br.set_current_limit(11500);

	fl.set_voltage_limit(11500);
	fr.set_voltage_limit(11500);
	bl.set_voltage_limit(11500);
	br.set_voltage_limit(11500);

	// Lifts
	frontLift.set_brake_mode(MOTOR_BRAKE_BRAKE);
	backLift.set_brake_mode(MOTOR_BRAKE_BRAKE);

	// INITIALIZE pnuematics
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
void autonomous() {
	hookClaw();
	unhookClaw();
}

// OPCONTROL FUNCTIONS

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

// Moves the front lift up and down - partner controller.
void driveFrontLift() {
	if(partner.get_digital(DIGITAL_R1)==1) {
		frontLift.move(127);
	}
	else if(partner.get_digital(DIGITAL_R2)) {
		frontLift.move(-127);
	}
	else
	{
		frontLift.move(0);
	}
}

// Moves the back lift up and down - partner controller.
void driveBackLift() {
	if(partner.get_digital(DIGITAL_L1)==1) {
		backLift.move(127);
	}
	else if(partner.get_digital(DIGITAL_L2)) {
		backLift.move(-127);
	}
	else
	{
		backLift.move(0);
	}
}

// Moves the claw up and down - partner controller.
void driveClaw() {
	if(partner.get_digital(DIGITAL_A)==1) {
		claw.set_value(0);
	}
	else if(partner.get_digital(DIGITAL_B))
	claw.set_value(1);
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
		driveClaw();
		driveBackLift();
		delay(20);
	}
}

// AUTONOMOUS FUNCTIONS

// MOVE and TURN

// Encoders
const double encoderPerInch = 35;
const double encoderPerDegreeTurn = 3.94;

// Speed
const double defaultSpeed = 127;
const double defaultTurnSpeed = 127;

double minSpeed = 35;
double maxSpeed = 127;

// Accelerator
double accelerator = 0.0095;
double turnAccelerator = 0.00095;

// MOVE

void move(double distanceInInches, double speedLimit) {
	// reset base motors
	fl.tare_position();
	fr.tare_position();
	bl.tare_position();
	br.tare_position();

	int startTime = millis();
	int maxTime = startTime + 100 + 70 * fabs(distanceInInches);

	int directMultiplier = 1;
	if (distanceInInches < 0)
	directMultiplier = -1;

	double distanceInEncoders = distanceInInches * encoderPerInch;

	double current = 0;
	double error = distanceInEncoders - current;
	double progress = current;
	double speed;

	while ((fabs(error) > 10 ) && (millis() < maxTime)) {
		current = (fl.get_position() + bl.get_position() + fr.get_position() +
		br.get_position())/4;

		error = distanceInEncoders - current;
		progress = current;
		speed = minSpeed + accelerator * progress * error;

		double currentVelocity = fabs((fl.get_actual_velocity() +
		fr.get_actual_velocity() + bl.get_actual_velocity() +
		br.get_actual_velocity()) / 4);

		if (speed > speedLimit) {
			speed = speedLimit;
		}

		// deacceleration code
		double maxDeaccelerationSpeed = 3.5 * sqrt(error);
		if (currentVelocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;

		speed = speed * directMultiplier;

		fl.move(speed);
		fr.move(speed);
		bl.move(speed);
		br.move(speed);

		delay(10);
	}

	// stop base motors
	fl.move(0);
	fr.move(0);
	bl.move(0);
	br.move(0);

	delay(10); // let motors fully stop
}

// TURN

double getAngle() {
	/* We use the inertial sensor to get the angle of the robot. This is used in
	our turn funtion. */
	double angle = inertial.get_heading();

	if (angle > 180)
	angle = angle - 360;
	else if (angle <= -180)
	angle = 360 + angle;
	return angle;
}

void turn (double angle, int speedLimit) {
	bool notAtTarget = true;

	// reset motors
	fl.tare_position();
	fr.tare_position();
	bl.tare_position();
	br.tare_position();

	double startAngle = getAngle(); // startAngle is the current angle of robot
	double targetAngle = startAngle + angle;
	double start = 0;
	double target = angle * encoderPerDegreeTurn;
	double current = 0;
	double directionMultiplier = 1;
	int startTime = millis();
	int maxTime = startTime + 20 * fabs(angle);

	if (target < start)
	directionMultiplier = -1;
	while(notAtTarget) {

		double current = (fl.get_position() - fr.get_position() - br.get_position() \
		+ bl.get_position())/4;

		double error = (target - current);
		double progress = current - start;
		double speed = minSpeed + 20 + fabs(turnAccelerator * progress * error);
		double maxDeaccelerationSpeed = 4 * sqrt(error);

		double currentVelocity = fabs((fl.get_actual_velocity() +
		fr.get_actual_velocity() + bl.get_actual_velocity() +
		br.get_actual_velocity()) / 4);

		if (currentVelocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;
		if (speed > speedLimit)
		speed = speedLimit;

		speed = speed * directionMultiplier;

		fl.move(speed);
		fr.move(- speed);
		bl.move( speed);
		br.move(- speed);

		double currentAngle = getAngle();
		double errorAngle = targetAngle - currentAngle;

		if (errorAngle > 180)
		errorAngle = errorAngle - 360;
		else if (errorAngle <= -180)
		errorAngle = 360 + errorAngle;
		if ( (fabs (error) < 10) || (fabs(errorAngle) < 0.75) || (millis() >
		maxTime) ) {

			fl.move(0);
			fr.move(0);
			bl.move(0);
			br.move(0);

			notAtTarget = false;

			lcd::print(8, "error: %f", error);
			//  lcd::print(8, "errorAngle: %f", errorAngle);
		}
		delay (5);
	}
	delay(50); // let motors stop
}

// LIFTS

// fix
void liftFrontLift() {
	frontLift.move(127);
}

// fix
void lowerFrontLift() {
	frontLift.move(-127);
}

// fix
void liftBackLift() {
	backLift.move(127);
}

// fix
void lowerBackLift() {
	backLift.move(-127);
}

// CLAW

void hookClaw() {
	claw.set_value(1);
}

void unhookClaw() {
	claw.set_value(0);
}

// fifteen second autonomous

void fifteenSecondAutonomousRightSide() {
	// move();
	// lowerClaw();
	// liftFrontLift();
	// move();
	// turn(-45);
	// lowerFrontLift();
	// liftClaw();

}

void fifteenSecondAutonomousLeftSide() {

}

// skills autonomous

void calibrateMotor() {
	inertial.get_heading();
	move(24, 127);
	delay(100);
	pros::lcd::print(2, "fl: %f", fl.get_position() );
	pros::lcd::print(3, "bl: %f", bl.get_position() );
	pros::lcd::print(4, "fr: %f", fr.get_position() );
	pros::lcd::print(5, "br: %f", br.get_position() );
	pros::lcd::print(6, "avg: %f", (fl.get_position() + bl.get_position() +
	fr.get_position() + br.get_position() )/4 );
	pros::lcd::print(7, "angle: %f", inertial.get_heading() );
	delay(10000);
}
