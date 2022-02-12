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
const double encoderPerInch = 58.0; // [360/3.25(perimeter of wheel)] / pi // old one 25
const double encoderPerDegreeTurn = 3.4; // CHANGE old - 2.6

// speed
const double defaultSpeed = 127.0;
const double defaultTurnSpeed = 127.0;

double minSpeed = 35.0; // CHMAGE
double turnMinSpeed = 35.0; // CHNAGE
double maxSpeed = 127.0;

// accelerators
double accelerator = 0.1; // 0.0095 // CHANGE
double turnAccelerator = 0.008; // CHANGE
double maxDeaccelerationSpeed;
double deaccelFactor = 6.0; // 4.25 CHANGE
double turnDeaccelFactor = 4.0; // CHANGE

void speedControlForSkills() {
	accelerator = 0.0095; // CHANGE
	deaccelFactor = 4.25; // CHANGE
}

// double getAngle()
// {
// 	double current_heading	= inertial.get_heading();
//
// 	if(current_heading > 180)
// 	current_heading	= current_heading - 360.0;
// 	else if(current_heading <=-180)
// 	current_heading	= current_heading + 360.0;
//
// 	return current_heading;
// }
// move
void move(double distanceInInches, double speedLimit, bool operateClaw) {
	// "resets" motors
	fl.tare_position();
	bl.tare_position();
	bl2.tare_position();
	fr.tare_position();
	br.tare_position();
	br2.tare_position();

	double startAngle = getAngle();

	int startTime = millis();
	int maxTime = startTime + 100.0 + 70.0 * fabs(distanceInInches); // CHANGE?

	int directMultiplier = 1.0;
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

	while ((fabs(error) > 15.0) && (millis() < maxTime)) { // CHANGE
		current = (fl.get_position() + bl.get_position() + bl2.get_position() +
		fr.get_position() + br.get_position() + br2.get_position()) / 6.0;
		progress=current;


		error = distanceInEncoders - current;
		currentAngle = getAngle();
		changeAngle = currentAngle - startAngle;

		if(operateClaw && (fabs(error) < 60.0))
			{
				hookFrontClaw();
				operateClaw = false;
			}

		speed = minSpeed + accelerator * progress * error;

		// "currentVelocity" equals the average/mean of the base motors
		double currentVelocity = fabs((fl.get_actual_velocity() +
		+ bl.get_actual_velocity() + bl2.get_actual_velocity() +
		fr.get_actual_velocity() + br.get_actual_velocity() +
		br2.get_actual_velocity()) / 6.0);

		if (speed > speedLimit) {
			speed = speedLimit;
		}

		// deacceleration
		maxDeaccelerationSpeed = deaccelFactor * sqrt(error);
		if (currentVelocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;

		speed = speed * directMultiplier;
		headingCorrection = changeAngle * 5.0 * directMultiplier;

		fl.move(speed - headingCorrection);
		fr.move(speed + headingCorrection);
		bl.move(speed - headingCorrection);
		br.move(speed + headingCorrection);
		bl2.move(speed - headingCorrection);
		br2.move(speed + headingCorrection);

		delay(10);
	}

	// stop base motors
	fl.move(0);
	bl.move(0);
	bl2.move(0);
	fr.move(0);
	br.move(0);
	br2.move(0);

	delay(10);
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
		if ((fabs (error) < 10.0) || (fabs(errorAngle) < 1.0) || (millis() >
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

// LIFTS

// lift the front lift completely
void liftLift() {
	frontLift.move(127);
	delay(1100); // CHANGE
	frontLift.move(0);
}

// lower the front lift completely
void lowerLift() {
	frontLift.move(-127);
	delay(1100); // CHANGE
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
