// set "motor" pnuematics
// initizalize pnuematics
// driver penumatics
// auton function pnuematics
// fifteen second pnuematics
// tune driver code
// move Function
// turn Function - add inertial sensor to robot
// fifteen second autons
// skills auton
// comment code
// put code in notebook

#include "main.h"
#include "math.h"

using namespace pros;

Motor fr(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // front right
Motor fl(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // front left
Motor br(21, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // back right
Motor bl(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // back left

Motor frontLift(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor backLift(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor claw(15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // CHANGE THIS

/* Instead of having one person control the whole robot, we use partner
controls. The master controller is used by Srihith and controls the robot's
base. The partner controller is used by Kriya and controls the robot's front and
back lift's and lever. */
Controller master(E_CONTROLLER_MASTER); // base - Srihith
Controller partner(E_CONTROLLER_PARTNER); // lifts, lever - Kriya

/* The inertial sensor is a 3-axis accelerometer and gyroscope. The
accelerometer measures linear acceleration of the robot, while the gyroscope
measures the rate of rotation about the inertial sensor 3-axis.*/
Imu inertial(0);

/* Runs initialization code. This occurs as soon as the program is started. All
other competition modes are blocked by initialize. */
void initialize() {
inertial.reset();
delay(5000);
lcd::initialize();

lcd::set_text(0, "81X");
lcd::print(3, "IMU heading: %3f", getAngle()); // WHY ERROR

// INITIALIZE MOTORS

// Base
fl.set_brake_mode(MOTOR_BRAKE_COAST);
fr.set_brake_mode(MOTOR_BRAKE_COAST);
bl.set_brake_mode(MOTOR_BRAKE_COAST);
br.set_brake_mode(MOTOR_BRAKE_COAST);

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

// Claw
// CHANGE THIS
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
	calibrateMotor();
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

void driveFrontLift() {
	if(partner.get_digital(DIGITAL_R1)==1) {
		frontLift.move(127);
	}
	else if(partner.get_digital(DIGITAL_R2))
	frontLift.move(-127);
}

void driveClaw() {
	if(partner.get_digital(DIGITAL_A)==1) {
		claw.move(127);
	}
	else if(partner.get_digital(DIGITAL_B))
		claw.move(-127);
}

void driveBackLift() {
	if(partner.get_digital(DIGITAL_L1)==1) {
		backLift.move(127);
	}
	else if(partner.get_digital(DIGITAL_L2))
	backLift.move(-127);
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

// MOVE

// encoders
const double encoderPerInch = 18.65;
const double encoderPerDegreeTurn = 3.63;

// speed
const double defaultSpeed = 127;
const double defaultTurnSpeed = 127;

double minSpeed = 35;
double maxSpeed = 127;

// accelerator
double accelerator = 0.00095;

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

/* We use the inertial sensor to get the angle of the robot. This is used in
our turn funtion. */
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

	// reset motors
	fl.tare_position();
	fr.tare_position();
	bl.tare_position();
	br.tare_position();

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
	  double speed = minSpeed + 20 + fabs(accelerator * progress * error);
	  double maxDeaccelerationSpeed = 4 * sqrt(error);

		double current_velocity = fabs((fl.get_actual_velocity() +
		fr.get_actual_velocity() + bl.get_actual_velocity() +
		br.get_actual_velocity()) / 4);

		if (current_velocity > maxDeaccelerationSpeed)
		speed = maxDeaccelerationSpeed;
		if (speed > speedLimit)
		speed = speedLimit;

		speed = speed * directionMultiplier;

		fl.move(speed);
		fr.move(- speed);
		bl.move( speed);
		br.move(- speed);

		double current_angle = getAngle();
		double error_angle = targetAngle - current_angle;

		if (error_angle > 180)
		error_angle = error_angle - 360;
		else if (error_angle <= -180)
		error_angle = 360 + error_angle;
		if ( (fabs (error) < 10) || (fabs(error_angle) < 0.75) || (millis() >
		maxTime) ) {

			fl.move(0);
			fr.move(0);
			bl.move(0);
			br.move(0);

			notAtTarget = false;

			lcd::print(8, "error: %f", error);
			//  lcd::print(8, "error_angle: %f", error_angle);
		}
		delay (5);
	}
	delay(70); // let motors stop
}


void liftFront() {
	frontLift.move(127);
}

void lowerFront() {
	frontLift.move(-127);
}

void liftClaw() {
	claw.move(127);
}

void lowerClaw() {
	claw.move(-127);
}

void liftBack() {
	backLift.move(127);
}

void lowerBack() {
	backLift.move(-127);
}

// fifteen second autonomous

void fifteenSecondAutonomous() {

}

// skills autonomous

void calibrateMotor() {
  inertial.get_heading();
  turn(90, 60);
  delay(100);
  pros::lcd::print(2, "fl: %f", fl.get_position() );
  pros::lcd::print(3, "bl: %f", bl.get_position() );
  pros::lcd::print(4, "fr: %f", fr.get_position() );
  pros::lcd::print(5, "br: %f", br.get_position() );
  pros::lcd::print(6, "avg: %f", (fl.get_position() + bl.get_position() +
	fr.get_position()+br.get_position() )/4 );
  pros::lcd::print(7, "angle: %f", inertial.get_heading() );
  delay(10000);
}
