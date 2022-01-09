#include "main.h"

#include "math.h"

using namespace pros;

// MOVE AND TURN

// encoders
/* Throughout the code the built-in encoder are used. They track the robot's
rotational position and velocity. */
const double encoderPerInch = 35;
const double encoderPerDegreeTurn = 4.05;

// speed
const double defaultSpeed = 127;
const double defaultTurnSpeed = 127;

double minSpeed = 35;
double maxSpeed = 127;

// accelerators
double accelerator = 0.0095;
double turnAccelerator = 0.009;

// move
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

	// "get_position" gets the absolute position of the motor in its encoder units
	while ((fabs(error) > 10 ) && (millis() < maxTime)) {
		current = (fl.get_position() + bl.get_position() + bl2.get_position() +
		fr.get_position() + br.get_position() + br2.get_position())/6;

		error = distanceInEncoders - current;
		progress = current;
		speed = minSpeed + accelerator * progress * error;

		// "get_actual_velocity" gets the actual velocity of the motor
		// "currentVelocity" equals the average/mean of the base motors
		double currentVelocity = fabs((fl.get_actual_velocity() +
		+ bl.get_actual_velocity() + bl2.get_actual_velocity() +
		fr.get_actual_velocity() + br.get_actual_velocity() +
		br2.get_actual_velocity()) / 6);

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


void turn (double angle, int speedLimit) {
	// robot is "notAtTarget"
	bool notAtTarget = true;

	/* reset motors - "tare_position" sets the "absolute" zero position of the
	motor to its current position */
	fl.tare_position();
	bl.tare_position();
	bl2.tare_position();
	fr.tare_position();
	br.tare_position();
	br2.tare_position();

	// the "startAngle" is the angle the inertial sensor gets
	double startAngle = getAngle();
	double targetAngle = startAngle + angle;
	double start = 0;
	double target = angle * encoderPerDegreeTurn;
	double current = 0;
	double directionMultiplier = 1;
	int startTime = millis();
	// WHY 20?
	int maxTime = startTime + 20 * fabs(angle);

	if (target < start)
	directionMultiplier = -1;
	while(notAtTarget) {

		double current = (fr.get_position() - br.get_position() - br2.get_position()
		+ bl.get_position() + fl.get_position() + bl2.get_position()) / 6;

		double error = (target - current);
		double progress = current - start;
		double speed = minSpeed + 20 + fabs(turnAccelerator * progress * error);
		double maxDeaccelerationSpeed = 6 * sqrt(error);

		// "get_actual_velocity" gets the actual velocity of the motor.
		double currentVelocity = fabs((fl.get_actual_velocity() +
		bl.get_actual_velocity() + bl2.get_actual_velocity() +
		fr.get_actual_velocity() + br.get_actual_velocity() +
		br2.get_actual_velocity()) / 6);

		if (currentVelocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;
		if (speed > speedLimit)
		speed = speedLimit;

		speed = speed * directionMultiplier;

		fl.move(speed);
		bl.move(speed);
		bl2.move(speed);
		fr.move(-speed);
		br.move(-speed);
		br2.move(-speed);

		// The current angle of the robot it the heading the inertial sensor gets.
		double currentAngle = getAngle();
		// Example: 90 - 47 = 43 degrees left
		double errorAngle = targetAngle - currentAngle;

		if (errorAngle > 180)
		errorAngle = errorAngle - 360;
		else if (errorAngle <= -180)
		errorAngle = 360 + errorAngle;
		if ((fabs (error) < 10) || (fabs(errorAngle) < 0.75) || (millis() >
		maxTime)) {

			// stop the base motors
			fl.move(0);
			bl.move(0);
			bl2.move(0);
			fr.move(0);
			br.move(0);
			bl2.move(0);

			// robot is now at target angle
			notAtTarget = false;
			lcd::print(8, "error: %f", error);
		}
		delay (5);
	}
	delay(50); // let base come to a complete stop
}

// LIFTS

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
/*
void hookBackClaw() {
	backClaw.set_value(0);
}

void unhookBackClaw() {
	backClaw.set_value(1);
}
*/
// RING INTAKE

void intakeRingIntake() {
	ringIntake.move(50);
}

void outtakeRingIntake() {
	ringIntake.move(-50);
}

void stopRingIntake() {
	ringIntake.move(0);
}

/* "calibrateMotor" is used for testing purposes. We were sturgginling to tune
our encoderPerDegreeTurn and turnAccelerator blindly, so this function allows us
to see how far off the angle the robot went compared to the target angle. */
void calibrateMotor() {
	/* "get_heading" gets the inertial sensor's heading relative to the initial
	direction of its x-axis */
	inertial.get_heading();
	turn(90, 127);
	delay(100);
	// gets the position of each base motor and displays them on the LCD screen
	// "get_position" gets the absolute position of the motor in its encoder units
	pros::lcd::print(2, "fl: %f", fl.get_position());
	pros::lcd::print(3, "bl: %f", bl.get_position());
	pros::lcd::print(4, "b12: %f", bl2.get_position());
	pros::lcd::print(5, "fr: %f", fr.get_position());
	pros::lcd::print(6, "br: %f", br.get_position());
	pros::lcd::print(7, "br2: %f", br2.get_position());
	/* gets the average position of the base motors and displays it on the LCD
	screen - "get_position" gets the absolute position of the motor in its encoder
	units */
	pros::lcd::print(8, "avg: %f", (fl.get_position() + bl.get_position() +
	bl2.get_position() + fr.get_position() + br.get_position() +
	br2.get_position())/6);
	/* "get_heading" gets the inertial sensor’s heading relative to the initial
	direction of its x-axis */
	pros::lcd::print(9, "angle: %f", inertial.get_heading() );
	delay(10000);
}
