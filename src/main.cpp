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

// OPCONTROL FUNCTIONS

/* "Arcade" control for base. One joystick is used to control
the base. The Y axis controls forward and backward motion and the X axis
controls turning motion. Function gets analog of joystick and "sends" them to
the base motors.*/
void drive() {
	/* "get_analog" gets the value of the analog channel (joystick) on the
	controller */
	float drives = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
	float turns = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

	// "move" sets the voltage for the motor from -127 to 127
	fr.move(drives - turns);
	br.move(drives - turns);
	br2.move(drives - turns);
	fl.move(drives + turns);
	bl.move(drives + turns);
	bl2.move(drives + turns);
}

// Moves the front lift up and down.
void driveFrontLift() {
	/* "get_digital" checks if a digital channel "button" on the controller is
	currently pressed */
	// "move" sets the voltage for the motor from -127 to 127
	if(master.get_digital(DIGITAL_R1)==1) {
		frontLift.move(127);
	}
	else if(master.get_digital(DIGITAL_R2)) {
		frontLift.move(-127);
	}
	else
	{
		frontLift.move(0);
	}
}

// Moves the front claw up and down.
void drivefrontClaw() {
	//  0 and 1 are states of the pnuematics.
	if(master.get_digital(DIGITAL_X)==1) {
		frontClaw.set_value(0);
	}
	else if(master.get_digital(DIGITAL_Y))
		frontClaw.set_value(1);
}

// Moves the front claw up and down.
void driveBackClaw() {
	//  0 and 1 are states of the pnuematics.
	if(master.get_digital(DIGITAL_A)==1) {
		backClaw.set_value(0);
	}
	else if(master.get_digital(DIGITAL_B))
		backClaw.set_value(1);
}

// Moves ring conveyor.
void driveRingIntake() {
	if(master.get_digital(DIGITAL_L1)==1) {
		ringIntake.move(127);
	}
	else if(master.get_digital(DIGITAL_L2)) {
		ringIntake.move(-127);
	}
	else
	{
		ringIntake.move(0);
	}
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

// AUTONOMOUS FUNCTIONS

// Move and Turn

// Encoders
const double encoderPerInch = 35;
const double encoderPerDegreeTurn = 4.05;

// Speed
const double defaultSpeed = 127;
const double defaultTurnSpeed = 127;

double minSpeed = 35;
double maxSpeed = 127;

// Accelerator
double accelerator = 0.0095;
double turnAccelerator = 0.009;

// Move
void move(double distanceInInches, double speedLimit) {
	/* "tare_position" sets the “absolute” zero position of the motor to its
	current position. */
	fl.tare_position();
	bl.tare_position();
	bl2.tare_position();
	fr.tare_position();
	br.tare_position();
	br2.tare_position();

	// "mills" gets the number of milliseconds since PROS initialized.
	int startTime = millis();
	// "fabs" gets the absolute value.
	int maxTime = startTime + 100 + 70 * fabs(distanceInInches);

	int directMultiplier = 1;
	if (distanceInInches < 0)
	directMultiplier = -1;

	double distanceInEncoders = distanceInInches * encoderPerInch;

	double current = 0;
	double error = distanceInEncoders - current;
	double progress = current;
	double speed;

// ADD EXTRA MOTORS

  // "get_position" gets the absolute position of the motor in its encoder units
	while ((fabs(error) > 10 ) && (millis() < maxTime)) {
		current = (fl.get_position() + bl.get_position() + fr.get_position() +
		br.get_position())/4;

		error = distanceInEncoders - current;
		progress = current;
		speed = minSpeed + accelerator * progress * error;

		// "get_actual_velocity" gets the actual velocity of the motor
		double currentVelocity = fabs((fl.get_actual_velocity() +
		fr.get_actual_velocity() + bl.get_actual_velocity() +
		br.get_actual_velocity()) / 4);

		if (speed > speedLimit) {
			speed = speedLimit;
		}

		// deacceleration
		double maxDeaccelerationSpeed = 3.5 * sqrt(error);
		if (currentVelocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;

		speed = speed * directMultiplier;

		fl.move(speed);
		bl.move(speed);
		bl2.move(speed);
		fr.move(speed);
		br.move(speed);
		br2.move(speed);

		delay(10);
	}

	// stop base motors
	fl.move(0);
	bl.move(0);
	bl2.move(0);
	fr.move(0);
	br.move(0);
	br2.move(0);

	delay(10); // let motors fully stop
}

// Turn

double getAngle() {
	/* "get_heading" gets the inertial sensor’s heading relative to the initial
	direction of its x-axis */
	double angle = inertial.get_heading();

	if (angle > 180)
	angle = angle - 360;
	else if (angle <= -180)
	angle = 360 + angle;
	return angle;
}

// ADD EXTRA MOTORS

void turn (double angle, int speedLimit) {
	// The robot is not at the target angle.
	bool notAtTarget = true;

	// reset motors
	fl.tare_position();
	bl.tare_position();
	bl2.tare_position();
	fr.tare_position();
	br.tare_position();
	br2.tare_position();

	double startAngle = getAngle();
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

		// "get_actual_velocity" gets the actual velocity of the motor.
		double currentVelocity = fabs((fl.get_actual_velocity() +
		fr.get_actual_velocity() + bl.get_actual_velocity() +
		br.get_actual_velocity()) / 4);

		if (currentVelocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;
		if (speed > speedLimit)
		speed = speedLimit;

		speed = speed * directionMultiplier;

		fl.move(speed);
		fr.move(-speed);
		bl.move(speed);
		br.move(-speed);

		// The current angle of the robot it the heading the inertial sensor gets.
		double currentAngle = getAngle();
		// Example: 90 - 47 = 43 degrees left
		double errorAngle = targetAngle - currentAngle;

		if (errorAngle > 180)
		errorAngle = errorAngle - 360;
		else if (errorAngle <= -180)
		errorAngle = 360 + errorAngle;
		if ( (fabs (error) < 10) || (fabs(errorAngle) < 0.75) || (millis() >
		maxTime) ) {

			// stop the base motors
			fl.move(0);
			fr.move(0);
			bl.move(0);
			br.move(0);

			// robot is now at target angle
			notAtTarget = false;

			lcd::print(8, "error: %f", error);
		}
		delay (5);
	}
	delay(50); // let motors come to a complete stop
}

// Lifts

void liftFrontLift() {
	frontLift.move(-127);
	delay(1200);
	frontLift.move(0);
}

void lowerFrontLift() {
	frontLift.move(127);
	delay(1200);
	frontLift.move(0);
}

// CLAWS

// front claw

void hookFrontClaw() {
	frontClaw.set_value(0);
}

void unhookFrontClaw() {
	frontClaw.set_value(1);
}

// back claw

void hookBackClaw() {
	backClaw.set_value(0);
}

void unhookBackClaw() {
	backClaw.set_value(1);
}

// ring intake

void intakeRingIntake() {
	ringIntake(127);
}

void outtakeRingIntake() {
	ringIntake(-127);
}

void stopRingIntake() {
	ringIntake(0);
}

// Fifteen Second Autonomous

void rightSideAllianceGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing backwards
	move(-, 127); // reverse to alliance goal
	turn(45, 127); // turn to alliance goal
	move(-, 127); // reverse to touch alliance goal
	hookBackClaw(); // hook the back claw on alliance goal
	intakeRingIntake(); // start scoring preload rings on alliance goal
	move(, 127); // move alliance goal while scoring rings on it
}

void leftSideAllianceGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing left
	move(-, 127); // reverse to alliance goal
	hookBackClaw(); // hook the back claw on the alliance goal
	intakeRingIntake(); // start scoring preload rings on the alliance goal
	move(, 127); // move alliance goal while scoring rings on it
}

void rightSideAllianceGoalMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	move(-, 127); // reverse to alliance goal
	turn(-135, 127); // turn with the back facing the alliance goal
	move(-, 127); // reverse to alliance goal
	hookBackClaw(); // hook the back claw on the alliance goal
	intakeRingIntake(); // start scoring preload rings on the alliance goal
	move(, 127); // move goals while scoring preload rings on the alliance goal
}

void leftSideAllianceGoalMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(, 127); // move to mobile goal
	hookFrontClaw(); // hook front claw on mobile goal
	move(-, 127); // reverse to alliance goal
	turn(-90, 127); // turn so back faces the alliance goal
	move(-, 127); // reverse to alliance goal
	hookBackClaw(); // hook back claw on alliance goal
	intakeRingIntake(); // start scoring preload rings on the alliance goal
	move(, 127); // move goals while scoring preload rings on the alliance goal
}

void rightSideMobileGoalCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	move(, 127); // move to first mobile goal
	hookFrontClaw(); // hook front claw on first mobile goal
	move(, 127); // move to center of field
	turn(90, 127); // turn with back to center goal
	move(-, 127); // reverse to center goal
	hookBackClaw(); // hook back claw on center goal
	turn(45, 127); // turn with goals
	move(, 127); // move to alliance home zone scoring goals
}

void leftSideMobileGoalCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	move(, 127); // move to forst mobile goal
	hookFrontClaw(); // hook front claw on first mobile goal
	move(, 127); // move to center of the field
	turn(-90, 127); // turn with back to center goal
	move(-, 127); // reverse to center goal
	hookBackClaw(); // hook back claw on center goal
	turn(-45, 127); // turn with goals
	move(, 127); // move to alliamce home zone scoring goals
}

void rightSideMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	move(-, 127); // reverse to alliance zone
}

void leftSideMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	move(-, 127); // reverse to alliance zone
}

void rightSideCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	move(, 127);
	turn(-45, 127); // turn to center goal
	move(, 127); // move to center goal
	hookFrontClaw(); // hook front claw on center goal
	move(-, 127); // reverse to alliance home zone with center goal
}

void leftSideCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	move(, 127);
	turn(45, 127); // turn to center goal
	move(, 127); // move to center goal
	hookFrontClaw(); // hool front claw on center goal
	move(-, 127); // reverse to alliane home zone with center goal
}

// SKILLS AUTONOMOUS

void skillsAuton() {
}

// ADD EXTRA MOTORS

void calibrateMotor() {
	inertial.get_heading();
	turn(90, 127);
	delay(100);
	// gets the position of each base motor and displays them on the LCD screen
	// "get_position" gets the absolute position of the motor in its encoder units
	pros::lcd::print(2, "fl: %f", fl.get_position());
	pros::lcd::print(3, "bl: %f", bl.get_position());
	pros::lcd::print(4, "fr: %f", fr.get_position());
	pros::lcd::print(5, "br: %f", br.get_position());
	/* gets the average position of the base motors and displays it on the LCD
	screen */
	pros::lcd::print(6, "avg: %f", (fl.get_position() + bl.get_position() +
	fr.get_position() + br.get_position() )/4);
	/* "get_heading" gets the inertial sensor’s heading relative to the initial
	direction of its x-axis */
	pros::lcd::print(7, "angle: %f", inertial.get_heading() );
	delay(10000);
}
