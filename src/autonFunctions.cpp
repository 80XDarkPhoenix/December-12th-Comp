#include "main.h"
#include "math.h"

// encoders
/* During the first half of the sesson we used the V5 motors' built in encoders
for our move and turn functions. Although this worked, when the base skipped,
the base would not move the correct distance. To solve this problem, we decided
to use the optical shaft encoders whcih can measure both the position and
direction of rotation of a VEX shaft. This allows us the ability to calculate
the speed of the shaft, as well as the distance it has traveled. */
/* We use the const keyword to make sure the value cannot be changed once the
variable has been initialized. */
/* encoderPerInch = 360/circumference of wheels
	 360/(2 * pi * (3.25/2))
	 360/(2 * pi * 1.625)
	 360/(6.28318530718 * 1625)
	 360/10.2101761242
	 encoderPerInch = 35.2589 */
/* The final encoderPerInch was found based off the calculated value and tuned
using trial and error and printing encoder values. */
const double encoderPerInch = 41.0;
// encoderPerInch * (2pi*R (center of the turn to the encoder wheel)) / 360
const double encoderPerDegreeTurn = 10.05;

// speed
// The default speeds are the maximum velocity possible.
const double defaultSpeed = 127.0;
const double defaultTurnSpeed = 127.0;

double minSpeedFast = 110.0; // for moveFast()
double minSpeed = 40.0; // for move()
double turnMinSpeed = 50.0; // for turn()
double maxSpeed = 127.0; // maximum velocity possible

// accelerators
/* These are found through trial and error while testing the move and turn
functions. */
double accelerator = 0.1; // for move() and moveFast()
double turnAccelerator = 0.07; // for turn()
double maxDeaccelerationSpeed;
double deaccelFactor = 3.0; // for move()
double deaccelFactorFast = 9.0; // for moveFast()
double turnDeaccelFactor = 3.2; // for turn()

// resets base motors and encoder values
void resetBaseMotors() {
	/* tare_position() sets the "absolute" zero position of the motor to its
	current position */
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

// sets the voltage for the base motors to 0
void stopBaseMotors() {
	// move() sets the voltage for the motor from -127 to 127
	l1.move(0);
	r1.move(0);
	l2.move(0);
	r2.move(0);
	l3.move(0);
	r3.move(0);
	delay(100);
}

// move
void move(double distanceInInches, double speedLimit, bool operateClaw) {

	resetBaseMotors(); // reset base motors and encoder values

	// get_value() gets the number of ticks recorded by the encoder
	double rEStartValue = rEncoder.get_value();
	double lEStartValue = lEncoder.get_value();

	/* The start angle equals the heading the inertial sensor gets relative to its
	initial direction to its x-axis. */
	double startAngle = getAngle(); // for headingCorrection

	// millis() gets the number of milliseconds since PROS initialized
	int startTime = millis();
	int maxTime = startTime + 100.0 + 70.0 * fabs(distanceInInches);

	double directMultiplier = 1.0; // direction (forwards or backwards)
	// if the distanceInInches inputed is less than zero
	if (distanceInInches < 0.0)
	// then the directMultiplier is negative
	directMultiplier = -1.0;

	double distanceInEncoders = distanceInInches * encoderPerInch;

	// current is the mean of the encoder start values
	double current = (rEStartValue + lEStartValue) / 2.0;
	// error is the calculated distanceInEncoders minus the current
	double error = distanceInEncoders - current;
	double progress = current;
	double speed;
	double currentAngle = startAngle;
	double changeAngle = 0.0;
	double headingCorrection = 0.0;

	// millis() gets the number of milliseconds since PROS initialized
	int stime = millis();

	/* while the absolute value of the error is greater than 15.0 and it is not
	timed out */
	// 15.0 was found and tuned through testing
	while ((fabs(error) > 15.0) && (millis() < maxTime)) {
		// get_value() gets the value for the given ADI port
		// current is the mean of the encoder values minus their start values
		current = (rEncoder.get_value() - rEStartValue + lEncoder.get_value() -
		lEStartValue) / 2.0;

		progress = current;

		error = distanceInEncoders - current;
		currentAngle = getAngle();
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
				hookClaw();
				operateClaw = false;
			}

		// currentVelocity is the average/mean of the base motors
		double currentVelocity = fabs((l1.get_actual_velocity() +
		+ l2.get_actual_velocity() + l3.get_actual_velocity() +
		r1.get_actual_velocity() + r2.get_actual_velocity() +
		r3.get_actual_velocity()) / 6.0);

		// when while loop
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
		headingCorrection = changeAngle * 5;
	//	speed = 50.0;
	//	headingCorrection = 0;

		// moves base motors by speed +- headingCorrection
		l1.move(speed - headingCorrection);
		r1.move(speed + headingCorrection);
		l2.move(speed - headingCorrection);
		r2.move(speed + headingCorrection);
		l3.move(speed - headingCorrection);
		r3.move(speed + headingCorrection);

		delay(10);
	}

	pros::lcd::print(4, "t:%d,r:%d,l:%d,a:%f", millis() - stime,
	rEncoder.get_value(), lEncoder.get_value(), inertial.get_heading());

	// The velocity of the base motors is zero.
	stopBaseMotors();

}

void moveFast(double distanceInInches, double speedLimit, bool operateClaw) {

	resetBaseMotors();

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

	double distanceInEncoders = distanceInInches * encoderPerInch; //51.5

	double current = (rEStartValue + lEStartValue) / 2.0;
	double error = distanceInEncoders - current;
	double progress = current;
	double speed;
	double currentAngle = startAngle;
	double changeAngle = 0.0;
	double headingCorrection = 0.0;

	int stime = millis();

	/* while the absolute value of the error is greater than 15.0 and it is not
	timed out */
	while ((fabs(error) > 15.0) && (millis() < maxTime)) {

		current = (rEncoder.get_value() - rEStartValue + lEncoder.get_value() -
		lEStartValue) / 2.0;
		// current = (l1.get_position() + l2.get_position() + l3.get_position() +
		// r1.get_position() + r2.get_position() + r3.get_position()) / 6.0;

		progress = current;

		error = distanceInEncoders - current;
		currentAngle = getAngle();
		// The changeAngle equals the current angle minus the start angle.
		// Example: 2 = 92 - 90
		changeAngle = currentAngle - startAngle;

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
		else if (speed < minSpeedFast) {
			speed = minSpeedFast + 10;
		}

		// deacceleration
		/* The maxDeaccelerationSpeed = the product of the deaccelFactor and the
		square root of error. */
		maxDeaccelerationSpeed = deaccelFactorFast * sqrt(error);
		/* If the currentVelocity is greater than the maxDeaccelerationSpeed the
		speed equals the maxDeaccelerationSpeed. */
		if (currentVelocity > maxDeaccelerationSpeed)
			speed = maxDeaccelerationSpeed;

		// Speed equals the product of speed and directMultiplier.
		speed = speed * directMultiplier;

		// headingCorrection equals the product of the changleAngle and 2.
		headingCorrection = changeAngle * 0.1;
		headingCorrection = 1/(1+headingCorrection);

		// moves base motors by speed +- headingCorrection
		l1.move(speed * headingCorrection);
		r1.move(speed / headingCorrection);
		l2.move(speed * headingCorrection);
		r2.move(speed / headingCorrection);
		l3.move(speed * headingCorrection);
		r3.move(speed / headingCorrection);

		delay(10);

	}

	pros::lcd::print(5, "t:%d,r:%d,l:%d,a:%f", millis() - stime,
	rEncoder.get_value(), lEncoder.get_value(), inertial.get_heading());

	/* This allows for us to save time in our autonomous, and is especially
	important the "goal rush" in the 15 second autonomous period. Because most
	teams get to the goal extremely fast, the time it takes to hook the front
	claw can make or break if we get the goal. This will set the pneumatics
	during the movement instead of waiting until after the movement is complete,
	saving time. */
	/* if the boolean is set to true and the absolute value of the error is less
	than 60.0 */
	if(operateClaw)
		{
			claw.set_value(0);
			operateClaw = false;
		}

	// The velocity of the base motors is zero.
	stopBaseMotors();

}

void moveBack(double distanceInInches, double speedLimit, bool operateClaw) {

	resetBaseMotors(); // reset base motors and encoder values

	// get_value() gets the number of ticks recorded by the encoder
	double rEStartValue = rEncoder.get_value();
	double lEStartValue = lEncoder.get_value();

	/* The start angle equals the heading the inertial sensor gets relative to its
	initial direction to its x-axis. */
	double startAngle = 0.0; // for headingCorrection

	// millis() gets the number of milliseconds since PROS initialized
	int startTime = millis();
	int maxTime = startTime + 100.0 + 70.0 * fabs(distanceInInches);

	double directMultiplier = 1.0; // direction (forwards or backwards)
	// if the distanceInInches inputed is less than zero
	if (distanceInInches < 0.0)
	// then the directMultiplier is negative
	directMultiplier = -1.0;

	double distanceInEncoders = distanceInInches * encoderPerInch;

	// current is the mean of the encoder start values
	double current = (rEStartValue + lEStartValue) / 2.0;
	// error is the calculated distanceInEncoders minus the current
	double error = distanceInEncoders - current;
	double progress = current;
	double speed;
	double currentAngle = startAngle;
	double changeAngle = 0.0;
	double headingCorrection = 0.0;

	// millis() gets the number of milliseconds since PROS initialized
	int stime = millis();

	/* while the absolute value of the error is greater than 15.0 and it is not
	timed out */
	// 15.0 was found and tuned through testing
	while ((fabs(error) > 15.0) && (millis() < maxTime)) {
		// get_value() gets the value for the given ADI port
		// current is the mean of the encoder values minus their start values
		current = (rEncoder.get_value() - rEStartValue + lEncoder.get_value() -
		lEStartValue) / 2.0;

		progress = current;

		error = distanceInEncoders - current;
		currentAngle = getAngle();
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
				hookClaw();
				operateClaw = false;
			}

		// currentVelocity is the average/mean of the base motors
		double currentVelocity = fabs((l1.get_actual_velocity() +
		+ l2.get_actual_velocity() + l3.get_actual_velocity() +
		r1.get_actual_velocity() + r2.get_actual_velocity() +
		r3.get_actual_velocity()) / 6.0);

		// when while loop
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
		headingCorrection = changeAngle * 5;
	//	speed = 50.0;
	//	headingCorrection = 0;

		// moves base motors by speed +- headingCorrection
		l1.move(speed - headingCorrection);
		r1.move(speed + headingCorrection);
		l2.move(speed - headingCorrection);
		r2.move(speed + headingCorrection);
		l3.move(speed - headingCorrection);
		r3.move(speed + headingCorrection);

		delay(10);
	}

	pros::lcd::print(6, "t:%d,r:%d,l:%d,a:%f", millis() - stime,
	rEncoder.get_value(), lEncoder.get_value(), inertial.get_heading());

	// The velocity of the base motors is zero.
	stopBaseMotors();

}
// move
// void moveFast(double distanceInInches, double speedLimit, bool operateClaw) {
//
// 	resetBaseMotors();
//
// 	// get_value gets the number of ticks recorded by the encoder
// 	double rEStartValue = rEncoder.get_value();
// 	double lEStartValue = lEncoder.get_value();
//
// 	/* The start angle equals the heading the inertial sensor gets relative to its
// 	initial direction to its x-axis. */
// 	double startAngle = getAngle();
//
// 	int startTime = millis();
// 	int maxTime = startTime + 100.0 + 70.0 * fabs(distanceInInches);
//
// 	double directMultiplier = 1.0;
// 	if (distanceInInches < 0.0)
// 	directMultiplier = -1.0;
//
// 	double distanceInEncoders = distanceInInches * encoderPerInch;
//
// 	double current = (rEStartValue + lEStartValue) / 2.0;
// 	double error = distanceInEncoders - current;
// 	double progress = current;
// 	double speed;
// 	double currentAngle = startAngle;
// 	double changeAngle = 0.0;
// 	double headingCorrection = 0.0;
//
// 	int stime = millis();
//
// 	/* while the absolute value of the error is greater than 15.0 and it is not
// 	timed out */
// 	while ((fabs(error) > 15.0) && (millis() < maxTime)) {
// 		// current = (l1.get_position() + l1.get_position() + l3.get_position() +
// 		// r1.get_position() + r2.get_position() + r3.get_position()) / 6.0;
// 		current = (rEncoder.get_value() - rEStartValue + lEncoder.get_value() - lEStartValue) / 2.0;
//
// 		progress = current;
//
// 		error = distanceInEncoders - current;
// 		currentAngle = getAngle();
// 		// The changeAngle equals the current angle minus the start angle.
// 		// Example: 2 = 92 - 90
// 		changeAngle = currentAngle - startAngle;
//
// 		/* This allows for us to save time in our autonomous, and is especially
// 		important the "goal rush" in the 15 second autonomous period. Because most
// 		teams get to the goal extremely fast, the time it takes to hook the front
// 		claw can make or break if we get the goal. This will set the pneumatics
// 		during the movement instead of waiting until after the movement is complete,
// 		saving time. */
// 		/* if the boolean is set to true and the absolute value of the error is less
// 		than 60.0 */
// 		if(operateClaw && (fabs(error) < 60.0))
// 			{
// 				hookClaw();
// 				operateClaw = false;
// 			}
//
// 		// "currentVelocity" equals the average/mean of the base motors
// 		double currentVelocity = fabs((l1.get_actual_velocity() +
// 		+ l2.get_actual_velocity() + l3.get_actual_velocity() +
// 		r1.get_actual_velocity() + r2.get_actual_velocity() +
// 		r3.get_actual_velocity()) / 6.0);
//
// 		speed = currentVelocity + 10;
//
// 		/* If the current speed of the robot is greater than the speedLimit, the
// 		speed is set to the speedLimit. If the current speed is less than the
// 		minSpeed, than it increases by 10 every time it goes through the loop. */
// 		if (speed > speedLimit) {
// 			speed = speedLimit;
// 		}
// 		else if (speed < minSpeedFast) {
// 			speed = minSpeedFast + 100;
// 		}
//
// 		// deacceleration
// 		/* The maxDeaccelerationSpeed = the product of the deaccelFactor and the
// 		square root of error. */
// 		maxDeaccelerationSpeed = deaccelFactorFast * sqrt(error);
// 		/* If the currentVelocity is greater than the maxDeaccelerationSpeed the
// 		speed equals the maxDeaccelerationSpeed. */
// 		if (currentVelocity > maxDeaccelerationSpeed)
// 			speed = maxDeaccelerationSpeed;
//
// 		// Speed equals the product of speed and directMultiplier.
// 		speed = speed * directMultiplier;
//
// 		// headingCorrection equals the product of the changleAngle and 2.
// 		headingCorrection = changeAngle * 10;
// 	//	speed = 50.0;
// 	//	headingCorrection = 0;
//
// 		// moves base motors by speed +- headingCorrection
// 		l1.move(speed - headingCorrection);
// 		r1.move(speed + headingCorrection);
// 		l2.move(speed - headingCorrection);
// 		r2.move(speed + headingCorrection);
// 		l3.move(speed - headingCorrection);
// 		r3.move(speed + headingCorrection);
//
// 		delay(10);
// 	}
//
// 	pros::lcd::print(3, "time: %d", millis() - stime);
// 	// The velocity of the base motors is zero.
// 	stopBaseMotors();
//
// }
// TURN

// getAngle gets the robots angle compared to its starting position
double getAngle() {
	// starting position is found using the inertial sensor
	/* get_heading gets the inertial sensor's heading relative to the initial
	direction of its x-axis */
	double angle = inertial.get_heading();
	// if the angle is less than 180
	if (angle > 180)
	// the angle is the angle minus 360
	// ex: 2 = 2 - 360 = -358
	angle = angle - 360;
	// if the angle is less than or equal to 180
	else if (angle <= -180)
	// the angle is the sum of 360 and the angle
	angle = 360 + angle;
	return angle;
}

double normalizeAngle(double givenAngle)
{
	// if the angle is less than 180
	if (givenAngle > 180)
	// the angle is the angle minus 360
	// ex: 2 = 2 - 360 = -358
	givenAngle = givenAngle - 360;
	// if the angle is less than or equal to 180
	else if (givenAngle <= -180)
	// the angle is the sum of 360 and the angle
	givenAngle = 360 + givenAngle;

	return givenAngle;
}

void turn (double angle, int speedLimit) {
	bool notAtTarget = true;

	angle = normalizeAngle(angle);
	resetBaseMotors();

	double startAngle = getAngle();
	double targetAngle = normalizeAngle(startAngle + angle);

	double errorAngle = angle;
	double progressAngle = 0.0;
	double currentAngle = startAngle;

	double start = 0.0;
	double target = angle * encoderPerDegreeTurn;
	double current = 0.0;
	double directionMultiplier = 1.0;
	double speed = 0;
	double currentVelocity = 0;

	// millis() gets the number of milliseconds since PROS initialized/
	int startTime = millis();
	/* maxTime is the sum of number of milliseconds since PROS initialized and
	20.0 times the absolute value of the angle. We use 20.0 because we tested
	using trial and error. */
	int maxTime = startTime + 100.0 + 30.0 * fabs(angle);

	/* If the target is less than start (0.0), then the directionMultiplier is
	negative. */
	if (errorAngle < 0)
	directionMultiplier = -1.0;
	// while the robot is not at the target
	while(notAtTarget) {

		/* get_value() gets the number os ticks recorded by the encoder. There are
		360 ticks in one revolution. */
		// current is the ADD COMMENT
		double current = (-r1.get_position() - r2.get_position() - r3.get_position()
				+ l1.get_position() + l2.get_position() + l3.get_position()) / 6.0;
				// "currentVelocity" equals the average/mean of the base motors

		// error is the target minus the current.
		// example: 45 - 0 = 45

		currentAngle = getAngle();
		errorAngle = normalizeAngle(targetAngle - currentAngle);
		progressAngle = normalizeAngle(currentAngle - startAngle);

		double maxDeaccelerationSpeed = turnDeaccelFactor * sqrt(fabs(errorAngle)*20.0);

		// get_actual_velocity() gets the actual velocity of the motor
		/* currentVelocity is average of the absolute value of the sum of the actual
		velocity of the base motors */
	 currentVelocity = fabs(l1.get_actual_velocity()) +
		fabs(l2.get_actual_velocity()) + fabs(l3.get_actual_velocity()) +
		fabs(r1.get_actual_velocity()) + fabs(r2.get_actual_velocity()) +
		fabs(r3.get_actual_velocity());
		currentVelocity = currentVelocity/6.0;

		speed = currentVelocity + 10;

		if(speed < turnMinSpeed)
			speed = turnMinSpeed + 45;
		/* If the currentVelocity is greater than the maxDeaccelerationSpeedn then
		the speed equals the maxDeaccelerationSpeed. */
		if ( (currentVelocity > maxDeaccelerationSpeed))// || (fabs(errorAngle) < (fabs(changeAngleRate) * 100) ) )
		{
			speed = maxDeaccelerationSpeed;
		}
		/* If the speed is greater than the speed limit, then the speed equals the
		speed limit. */
		if (speed > speedLimit)
			speed = speedLimit;

		if (errorAngle < 0)
			directionMultiplier = -1.0;
		else
			directionMultiplier = 1.0;
		/* The speed is the speed times the directMultiplier (changes to positive or
		negative) */
		speed = speed * directionMultiplier;

		// move each base motor positively or negatively
		l1.move(speed);
		l2.move(speed);
		l3.move(speed);
		r1.move(-speed);
		r2.move(-speed);
		r3.move(-speed);

		pros::lcd::print(7, "angle: %f", getAngle());
		pros::lcd::print(8, "error angle: %f", errorAngle);

		/* If the absolute value of error is less than 15.0 or the error angle is
		less than 2 or it is timed out */
		if ( ( (fabs(errorAngle) < 1) && (fabs(currentVelocity) < 5.0) ) || (millis() > maxTime) ) {
			// stop the base motors
			stopBaseMotors();
			notAtTarget = false;
		}
		delay(10);
	}
}



void turn_old (double angle, int speedLimit) {
	bool notAtTarget = true;

	resetBaseMotors();

	double startAngle = getAngle();
	double targetAngle = startAngle + angle;
	double start = 0.0;
	double target = angle * encoderPerDegreeTurn;
	double current = 0.0;
	double directionMultiplier = 1;

	// millis() gets the number of milliseconds since PROS initialized/
	int startTime = millis();
	/* maxTime is the sum of number of milliseconds since PROS initialized and
	20.0 times the absolute value of the angle. We use 20.0 because we tested
	using trial and error. */
	int maxTime = startTime + 20.0 * fabs(angle);

	/* If the target is less than start (0.0), then the directionMultiplier is
	negative. */
	if (target < start)
	directionMultiplier = -1.0;
	// while the robot is not at the target
	while(notAtTarget) {

		/* get_value() gets the number os ticks recorded by the encoder. There are
		360 ticks in one revolution. */
		// current is the ADD COMMENT
		double current = (-r1.get_position() - r2.get_position() - r3.get_position()
				+ l1.get_position() + l2.get_position() + l3.get_position()) / 6.0;

		// error is the target minus the current.
		// example: 45 - 0 = 45
		double error = (target - current);
		// progress is the current minus the start (0.0)
		double progress = current - start;

		/* speed is the sum of the turnMinSpeed (ADD VALUE) and the absolute value
		of the product of the turnAccelerator (ADD VALUE), progress, and error */
		double speed = turnMinSpeed + fabs(turnAccelerator * progress * error);
		// maxDeaccelerationSpeed is the product of the turnDeaccelFactor (ADD VALUE) and the sqaure root of the error
		// ADD SCHOOL PHYSICS THING
		double maxDeaccelerationSpeed = turnDeaccelFactor * sqrt(error);

		// get_actual_velocity() gets the actual velocity of the motor
		/* currentVelocity is average of the absolute value of the sum of the actual
		velocity of the base motors */
		double currentVelocity = fabs((l1.get_actual_velocity() +
		l2.get_actual_velocity() + l3.get_actual_velocity() +
		r1.get_actual_velocity() + r2.get_actual_velocity() +
		r3.get_actual_velocity()) / 6.0);

		/* If the currentVelocity is greater than the maxDeaccelerationSpeedn then
		the speed equals the maxDeaccelerationSpeed. */
		if (currentVelocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;
		/* If the speed is greater than the speed limit, then the speed equals the
		speed limit. */
		if (speed > speedLimit)
		speed = speedLimit;

		/* The speed is the speed times the directMultiplier (changes to positive or
		negative) */
		speed = speed * directionMultiplier;

		// move each base motor positively or negatively
		l1.move(speed);
		l2.move(speed);
		l3.move(speed);
		r1.move(-speed);
		r2.move(-speed);
		r3.move(-speed);

		// currentAngle is the angle the intertial sensor gets.
		double currentAngle = getAngle();
		// errorAngle is the targetAngle minus the currentAngle.
		// ADD EXAMPLE
		double errorAngle = targetAngle - currentAngle;

		/* If the errorAngle is greater than 180, then the errorAngle equals the
		errorAngle minus 360. */
		if (errorAngle > 180)
		errorAngle = errorAngle - 360;
		/* If the error angle is less than or equal to -180, then the errorAngle is
		the sum of 360 and the errorAngle. */
		else if (errorAngle <= -180)
		errorAngle = 360 + errorAngle;
		/* If the absolute value of error is less than 15.0 or the error angle is
		less than 2 or it is timed out */
		if ((fabs (error) < 20.0) || (fabs(errorAngle) < 2.0) || (millis() >
		maxTime)) {

			// stop the base motors
			stopBaseMotors();

			notAtTarget = false;

		}
		delay(5);
	}
}


/* turnTo uses the turn logic but makes the turn correct based of the currentAngle
of the robot. If the robot needs to turn to 90 degrees instead of actually turning
90 degrees it will turn based off the angle it is already at. For example, if the
robot is at 3 degrees it turns to 90 degrees, but it actaully is only turning 87
degrees. */
void turnTo(double angle, int speedLimit) {
	// The currentAngle is the FILLIN
	double currentAngle = getAngle();
	// The turnAngle (the angle to robot turns) is the target angle FILLIN
	double turnAngle = normalizeAngle(angle - currentAngle);


	turn(turnAngle, speedLimit);
	// pros::lcd::print(6, "a: %d", getAngle());
}

void speed() {
	transmission.set_value(1);
}

void torque() {
	transmission.set_value(0);
}

// LIFT

// moves the lift at a set speed
void moveLift(double liftSpeed) {
	lift.move(liftSpeed);
}

// CLAWS
// set_value() sets the value for the given ADI port

// lowers the front claw
void hookClaw() {
	claw.set_value(0);
}

// lifts the front claw
void unhookClaw() {
	claw.set_value(1);
}

// lowers the back claw
void hookTilter() {
	tilterClamp.set_value(0);
	delay(25);
	tilter.set_value(0);
}

// lifts the back claw
void unhookTilter() {
	tilter.set_value(1);
	delay(50);
	tilterClamp.set_value(1);
}

// RING INTAKE

// moves the ring intake at a set speed
void moveRingIntake(double ringIntakeSpeed) {
	ringIntake.move(ringIntakeSpeed);
}
