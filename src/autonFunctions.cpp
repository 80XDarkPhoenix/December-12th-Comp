#include "main.h"
#include "math.h"

// encoders
/* WE USE SHAFT ENCODERDS */

/* We use the const keyword to make sure the value cannot be changed once the
variable has been initialized. */
// 360/circumference of wheels
const double encoderPerInch = 35.2589;
// encoderPerInch * (2pi*R (center of the turn to the encoder wheel))/ 360
const double encoderPerDegreeTurn = 6.02;

// speed
// The default speeds are the maximum speed possible.
const double defaultSpeed = 127.0;
const double defaultTurnSpeed = 127.0;

double minSpeed = 40.0;
double turnMinSpeed = 40.0;
// 127.0 is the maximum voltage for the motor
double maxSpeed = 127.0;

// accelerators
double accelerator = 0.1;
double turnAccelerator = 0.008;
double maxDeaccelerationSpeed;
double deaccelFactor = 6.0;
double turnDeaccelFactor = 3.5;

void resetBaseMotors() {
	/* sets the "absolute" zero position of the motor to its current position */
	l1.tare_position();
	r1.tare_position();
	l2.tare_position();
	r2.tare_position();
	l3.tare_position();
	r3.tare_position();
  // reset() sets the encoder values to zero
	rEncoder.reset();
	lEncoder.reset();
}

void stopBaseMotors() {
	// move() sets the voltage for the motor from -127 to 127

	// sets the voltage for the base motors to 0
	l1.move(0);
	r1.move(0);
	l2.move(0);
	r2.move(0);
	l3.move(0);
	r3.move(0);
}

// move
void move(double distanceInInches, double speedLimit, bool operateClaw) {

	resetBaseMotors();

	// get_value gets the number of ticks recorded by the encoder
	double rEStartValue = rEncoder.get_value();
	double lEStartValue = lEncoder.get_value();

	/* The start angle equals the heading the inertial sensor gets relative to its
	initial direction to its x-axis. */
	double startAngle = getAngle();

	int startTime = millis();
	int maxTime = startTime + 100.0 + 70.0 * fabs(distanceInInches);

	double directMultiplier = 1.0;
	if (distanceInInches < 0.0)
	directMultiplier = -1.0;

	double distanceInEncoders = distanceInInches * encoderPerInch;

	double current = 0.0;
	double error = distanceInEncoders - current;
	double progress = current;
	double speed;
	double currentAngle = startAngle;
	double changeAngle = 0.0;
	double headingCorrection = 0.0;

	/* while the absolute value of the error is greater than 15.0 and it is not
	timed out */
	while ((fabs(error) > 15.0) && (millis() < maxTime)) {
		// current = (l1.get_position() + l1.get_position() + l3.get_position() +
		// r1.get_position() + r2.get_position() + r3.get_position()) / 6.0;
		current = (rEncoder.get_value() - rEStartValue + lEncoder.get_value() - lEStartValue)/2;

		progress = current;

		error = distanceInEncoders - current;
		currentAngle = getAngle();
		// The changeAngle equals the current angle minus the start angle.
		// Example: 2 = 92 - 90
		changeAngle = currentAngle - startAngle;

		/* This allows for us to save time in our autonomous, and is especially
		important the "goal rush" in the 15 second autonomous period. Because most
		teams get to the goal extremely fast, the time it takes to hook the front
		claw can make or break if we get the goal. This will set the pneumatics
		during the movement instead of waiting until after the movement is complete,
		saving time. */
		/* if the boolean is set to true and the absolute value of the error is less
		than 60.0 */
		if(operateClaw && (fabs(error) < 60.0))
			{
				hookFrontClaw();
				operateClaw = false;
			}

		// "currentVelocity" equals the average/mean of the base motors
		double currentVelocity = fabs((l1.get_actual_velocity() +
		+ l2.get_actual_velocity() + l3.get_actual_velocity() +
		r1.get_actual_velocity() + r2.get_actual_velocity() +
		r3.get_actual_velocity()) / 6.0);

		speed = currentVelocity + 10;

		/* If the current speed of the robot is greater than the speedLimit, the
		speed is set to the speedLimit. If the current speed is less than the
		minSpeed, than it increases by 10 every time it goes through the loop. */
		if (speed > speedLimit) {
			speed = speedLimit;
		}
		else if (speed < minSpeed) {
			speed = minSpeed + 10;
		}

		// deacceleration
		/* The maxDeaccelerationSpeed = the product of the deaccelFactor and the
		square root of error. */
		maxDeaccelerationSpeed = deaccelFactor * sqrt(error);
		/* If the currentVelocity is greater than the maxDeaccelerationSpeed the
		speed equals the maxDeaccelerationSpeed. */
		if (currentVelocity > maxDeaccelerationSpeed)
			speed = maxDeaccelerationSpeed;

		// Speed equals the product of speed and directMultiplier.
		speed = speed * directMultiplier;
		// headingCorrection equals the product of the changleAngle and 2.
		headingCorrection = changeAngle * 2.0;

		// moves base motors by speed +- headingCorrection
		l1.move(speed - headingCorrection);
		r1.move(speed + headingCorrection);
		l2.move(speed - headingCorrection);
		r2.move(speed + headingCorrection);
		l3.move(speed - headingCorrection);
		r3.move(speed + headingCorrection);

		delay(10);
	}

	// The velocity of the base motors is zero.
	stopBaseMotors();

	delay(100);
}

// TURN

double getAngle() {
	double angle = inertial.get_heading();

	if (angle > 180)
	angle = angle - 360;
	else if (angle <= -180)
	angle = 360 + angle;
	return angle;
}

void turn (double angle, int speedLimit) {
	bool notAtTarget = true;

	resetBaseMotors();

	// gets the nummber of ticks recorded by the encoder
	double rEStartValue = rEncoder.get_value();
	double lEStartValue = lEncoder.get_value();

	double startAngle = getAngle();
	double targetAngle = startAngle + angle;
	double start = 0.0;
	double target = angle * encoderPerDegreeTurn;
	double current = 0.0;
	double directionMultiplier = 1;

	int startTime = millis();
	int maxTime = startTime + 20.0 * fabs(angle); // CHANGE

	if (target < start)
	directionMultiplier = -1.0;
	while(notAtTarget) {

		// current = average position of base motors (to turn)
		// double current = (-r1.get_position() - r2.get_position() - r3.get_position()
		// + l1.get_position() + l2.get_position() + l3.get_position()) / 6.0;

		double current = (-rEncoder.get_value() + rEStartValue + lEncoder.get_value() - lEStartValue)/2;

		double error = (target - current);
		double progress = current - start;

		double speed = turnMinSpeed  + fabs(turnAccelerator * progress * error);
		double maxDeaccelerationSpeed = turnDeaccelFactor * sqrt(error);

		// get_actual_velocity gets the actual velocity of the motor
		double currentVelocity = fabs((l1.get_actual_velocity() +
		l2.get_actual_velocity() + l3.get_actual_velocity() +
		r1.get_actual_velocity() + r2.get_actual_velocity() +
		r3.get_actual_velocity()) / 6.0);

		if (currentVelocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;
		if (speed > speedLimit)
		speed = speedLimit;

		speed = speed * directionMultiplier;

		l1.move(speed);
		l2.move(speed);
		l3.move(speed);
		r1.move(-speed);
		r2.move(-speed);
		r3.move(-speed);

		double currentAngle = getAngle();
		double errorAngle = targetAngle - currentAngle;

		if (errorAngle > 180)
		errorAngle = errorAngle - 360;
		else if (errorAngle <= -180)
		errorAngle = 360 + errorAngle;
		/* if the absolute value of error is less than 15.0 or the error angle is less than 2 or it is timed out
		if ((fabs (error) < 15.0) || (fabs(errorAngle) < 2.0) || (millis() >
		maxTime)) {

			// stop the base motors
			stopBaseMotors();

      delay(100);

			// used to tune turnEncoders and turnAccelerator
			pros::lcd::print(3, "a: %f", getAngle());
			pros::lcd::print(4, "e: %f", error);

			notAtTarget = false;
			lcd::print(8, "error: %f", error);

		}
		delay (5);
	}
	delay(100);
}

/* turnTo uses the turn logic but makes the turn correct based of the currentAngle
of the robot. If the robot needs to turn to 90 degrees instead of actually turning
90 degrees it will turn based off the angle it is already at. For example, if the
robot is at 3 degrees it turns to 90 degrees, but it actaully is only turning 87
degrees. */
void turnTo(double angle, int speedLimit) {
	double currentAngle = getAngle();
	double turnAngle = angle - currentAngle;
	turn(turnAngle, speedLimit);
}

// LIFT

// lifts the front lift completely
void liftLift() {
	frontLift.move(127);
	delay(1100);
	frontLift.move(0);
}

// lowers the front lift completely
void lowerLift() {
	frontLift.move(-127);
	delay(1100);
	frontLift.move(0);
}

// moves the lift at a set speed
void moveLift(double liftSpeed) {
	frontLift.move(liftSpeed);
}

// CLAWS

// lowers the front claw
void hookFrontClaw() {
	frontClaw.set_value(0);
}

// lifts the front claw
void unhookFrontClaw() {
	frontClaw.set_value(1);
}

// lowers the back claw
void hookBackClaw() {
	backClaw.set_value(0);
}

// lifts the back claw
void unhookBackClaw() {
	backClaw.set_value(1);
}

// RING INTAKE

// moves the ring intake at a set speed
void moveRingIntake(double ringIntakeSpeed) {
	ringIntake.move(ringIntakeSpeed);
}
