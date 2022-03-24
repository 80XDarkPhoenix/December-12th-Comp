#include "main.h"
#include "math.h"

// encoders
/* Throughout the code the built-in encoders are used. They track the robot's
rotational position and velocity. */

/* We use the const keyword to make sure the value cannot be changed once the
variable has been initialized. */
const double encoderPerInch = 51.5;
const double encoderPerDegreeTurn = 6.02;

// speed
/* The default speeds are the maximum speed possible. */
const double defaultSpeed = 127.0;
const double defaultTurnSpeed = 127.0;

double minSpeed = 30.0;
double turnMinSpeed = 35.0;
double maxSpeed = 127.0;

// accelerators
double accelerator = 0.1;
double turnAccelerator = 0.008;
double maxDeaccelerationSpeed;
double deaccelFactor = 6.0;
double turnDeaccelFactor = 3.5;

void resetBaseMotors() {
	fl.tare_position();
	bl.tare_position();
	bl2.tare_position();
	fr.tare_position();
	br.tare_position();
	br2.tare_position();
}

void stopBaseMotors() {
	fl.move(0);
	fr.move(0);
	bl.move(0);
	br.move(0);
	bl2.move(0);
	br2.move(0);
}

// move
void move(double distanceInInches, double speedLimit, bool operateClaw) {

	resetBaseMotors();

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

	while ((fabs(error) > 15.0) && (millis() < maxTime)) {
		current = (fl.get_position() + bl.get_position() + bl2.get_position() +
		fr.get_position() + br.get_position() + br2.get_position()) / 6.0;

		progress = current;

		error = distanceInEncoders - current;
		currentAngle = getAngle();
		changeAngle = currentAngle - startAngle;

		if(operateClaw && (fabs(error) < 60.0))
			{
				hookFrontClaw();
				operateClaw = false;
			}

		// "currentVelocity" equals the average/mean of the base motors
		double currentVelocity = fabs((fl.get_actual_velocity() +
		+ bl.get_actual_velocity() + bl2.get_actual_velocity() +
		fr.get_actual_velocity() + br.get_actual_velocity() +
		br2.get_actual_velocity()) / 6.0);

		// speed = minSpeed + accelerator * progress * error;
		speed = currentVelocity + 10;

		if (speed > speedLimit) {
			speed = speedLimit;
		}
		else if (speed < minSpeed) {
			speed = minSpeed;
		}

		// deacceleration
		maxDeaccelerationSpeed = deaccelFactor * sqrt(error);
		if (currentVelocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;

		speed = speed * directMultiplier;
		headingCorrection = changeAngle * 2.0;

		fl.move(speed - headingCorrection);
		fr.move(speed + headingCorrection);
		bl.move(speed - headingCorrection);
		br.move(speed + headingCorrection);
		bl2.move(speed - headingCorrection);
		br2.move(speed + headingCorrection);

		delay(10);
	}

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

	fl.tare_position();
	bl.tare_position();
	bl2.tare_position();
	fr.tare_position();
	br.tare_position();
	br2.tare_position();

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
		double current = (-fr.get_position() - br.get_position() - br2.get_position()
		+ bl.get_position() + fl.get_position() + bl2.get_position()) / 6.0;

		double error = (target - current);
		double progress = current - start;

		double speed = turnMinSpeed  + fabs(turnAccelerator * progress * error);
		double maxDeaccelerationSpeed = turnDeaccelFactor * sqrt(error);

		double currentVelocity = fabs((fl.get_actual_velocity() +
		bl.get_actual_velocity() + bl2.get_actual_velocity() +
		fr.get_actual_velocity() + br.get_actual_velocity() +
		br2.get_actual_velocity()) / 6.0);

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
		if ((fabs (error) < 15.0) || (fabs(errorAngle) < 2.0) || (millis() >
		maxTime)) {

			// stop the base motors
			fl.move(0);
			bl.move(0);
			bl2.move(0);
			fr.move(0);
			br.move(0);
			br2.move(0);

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
