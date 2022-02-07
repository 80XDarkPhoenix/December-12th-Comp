#include "main.h"
#include "math.h"

using namespace pros;

// move and turn

/* PROS Functions Used in Move and Turn Functions
- "tare_position" sets the “absolute” zero position of the motor to its
current position.
- "fabs" gets the absolute value.
- "mills" gets the number of milliseconds since PROS initialized.
- "get_actual_velocity" gets the actual velocity of the motor */

// encoders
/* Throughout the code the built-in encoders are used. They track the robot's
rotational position and velocity. */
const double encoderPerInch = 25; // [360/3.25(perimeter of wheel)] / pi
const double encoderPerDegreeTurn = 2.6;

// speed
const double defaultSpeed = 127;
const double defaultTurnSpeed = 127;

double minSpeed = 10;
double turnMinSpeed = 35;
double maxSpeed = 127;

// accelerators
double accelerator = 0.04;
double turnAccelerator = 0.008;
double maxDeaccelerationSpeed;

// move
void move(double distanceInInches, double speedLimit, bool operateClaw) {
	// "resets" motors
	fl.tare_position();
	bl.tare_position();
	bl2.tare_position();
	fr.tare_position();
	br.tare_position();
	br2.tare_position();

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

	while ((fabs(error) > 15) && (millis() < maxTime)) {
		current = (fl.get_position() + bl.get_position() + bl2.get_position() +
		fr.get_position() + br.get_position() + br2.get_position()) / 6.0;

		error = distanceInEncoders - current;
		progress = current;

		if(operateClaw && (fabs(error) < 60))
			{
				hookFrontClaw();
				operateClaw = false;
			}

		speed = minSpeed + accelerator * progress * error;

		// "currentVelocity" equals the average/mean of the base motors
		double currentVelocity = fabs((fl.get_actual_velocity() +
		+ bl.get_actual_velocity() + bl2.get_actual_velocity() +
		fr.get_actual_velocity() + br.get_actual_velocity() +
		br2.get_actual_velocity()) / 6);

		if (speed > speedLimit) {
			speed = speedLimit;
		}

		// deacceleration
		double maxDeaccelerationSpeed = 6.0 * sqrt(error);
		if (currentVelocity > maxDeaccelerationSpeed) 
		speed = maxDeaccelerationSpeed;

		speed = speed * directMultiplier;

		fl.move(speed);
		fr.move(speed);
		bl.move(speed);
		br.move(speed);
		bl2.move(speed);
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

// turn

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
	bool notAtTarget = true;

	// "resets" motors
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

		// current = average position of base motors (to turn)
		double current = (-fr.get_position() - br.get_position() - br2.get_position()
		+ bl.get_position() + fl.get_position() + bl2.get_position()) / 6;

		double error = (target - current);
		double progress = current - start;

		double speed = turnMinSpeed  + fabs(turnAccelerator * progress * error);
		double maxDeaccelerationSpeed = 4 * sqrt(error);

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

		double currentAngle = getAngle();
		double errorAngle = targetAngle - currentAngle;

		if (errorAngle > 180)
		errorAngle = errorAngle - 360;
		else if (errorAngle <= -180)
		errorAngle = 360 + errorAngle;
		if ((fabs (error) < 10.0) || (fabs(errorAngle) < 1.0) || (millis() >
		maxTime)) {

			// stop the base motors
			fl.move(0);
			bl.move(0);
			bl2.move(0);
			fr.move(0);
			br.move(0);
			br2.move(0);

			// let base motors stop
      delay(100);

			// used to tune turnEncoders and turnAccelerator
			pros::lcd::print(3, "a: %f", getAngle());
			pros::lcd::print(4, "e: %f", error);

			notAtTarget = false;
			lcd::print(8, "error: %f", error);
		}
		delay (5);
	}
	delay(100); // let base come to a complete stop
}

// LIFTS

// lift the front lift completely
void liftLift() {
	frontLift.move(127);
	delay(1100);
	frontLift.move(0);
}

// lower the front lift completely
void lowerLift() {
	frontLift.move(-127);
	delay(1100);
	frontLift.move(0);
}

// move the lift at a set speed
void moveLift(double liftSpeed) {
	frontLift.move(liftSpeed);
}

// claws

// lower the front claw
void hookFrontClaw() {
	frontClaw.set_value(1);
}

// lift the front claw
void unhookFrontClaw() {
	frontClaw.set_value(0);
}

// lower the back claw
void hookBackClaw() {
	backClaw.set_value(1);
}

// lift the back claw
void unhookBackClaw() {
	backClaw.set_value(0);
}

// ring intake

// move the ring intake at a set speed
void moveRingIntake(double ringIntakeSpeed) {
	ringIntake.move(ringIntakeSpeed);
}

// distance

/* gets the distance in inches from an object (perimeter wall) to the front
distance sensor */
double getFrontDistance() {
  double dist = 0;
  int index = 0;
  while ((index < 10) && (dist == 0)) {
  //  dist = frontDistance.get() * 0.0394; // converts distance to inches
    delay(5);
    index++;
  }
  return dist;
}

/* gets the distance in inches from an object (perimeter wall) to the back
distance sensor */
double getBackDistance() {
  double dist = 0;
  int index = 0;

  while ((index < 10) && (dist == 0)) {
  //  dist = backDistance.get()*0.0394;
    delay(5);
    index++;
  }
  return dist;
}

// move to goalDistanceFromWall using the front distance sensor
void frontDistanceMove(double goalDistanceFromWall)
{
  double actualDistanceFromWall = getFrontDistance();
  if(actualDistanceFromWall != 0)
  move(actualDistanceFromWall - goalDistanceFromWall, 110);
}

// move to goalDistanceFromWall using the front distance sensor
void backDistanceMove(double goalDistanceFromWall)
{
  double actualDistanceFromWall = getBackDistance();
  if (actualDistanceFromWall != 0)
  move(-actualDistanceFromWall + goalDistanceFromWall, 110);
}
