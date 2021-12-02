#include "main.h"
#include "math.h"

using namespace pros;

Motor fr(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // front right
Motor fl(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // front left
Motor br(21, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); // back right
Motor bl(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); // back left

Motor frontLift(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor backLift(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor lever(15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Imu inertial();

/* Instead of having one person control the wholuye robot, we use partner
controls. The master controller is used by Srihith and controls the robot's
base. The partner controller is used by Kriya and controls the robot's front and
back lift's and lever. */
Controller master(E_CONTROLLER_MASTER); // base - Srihith
Controller partner(E_CONTROLLER_PARTNER); // lifts, lever - Kriya

/* The inertial sensor is a 3-axis accelerometer and gyroscope. The
accelerometer measures linear acceleration of the robot, while the gyroscope
measures the rate of rotation about the inertial sensor 3-axis.*/
Imu inertial();

/* Runs initialization code. This occurs as soon as the program is started. All
other competition modes are blocked by initialize. */
void initialize() {
	lcd::initialize();
	lcd::set_text(1, "Hello PROS User!");
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
void autonomous() {}

// opcontrol functions

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

void driveLever() {
	if(partner.get_digital(DIGITAL_A)==1) {
		lever.move(127);
	}
	else if(partner.get_digital(DIGITAL_B))
		lever.move(-127);
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
		driveLever();
		driveBackLift();
		delay(20);
	}
}

// autonomous functions

// encoders
// const double encoderPerInch = ;
// const double encoderPerDegreeTurn = ;

// speed
const double defaultSpeed = 127;
const double defaultTurnSpeed = 127;

double minSpeed = 35;
double maxSpeed = 127;

// accelerator
// double accelerator =;

void move(double distanceInInches, double speedLimit) {
	 // reset base motors
   fl.tare_position();
   fr.tare_position();
   bl.tare_position();
   br.tare_position();

   int startTime = millis();
   int maxTime = startTime + 100 + 70*fabs(distanceInInches);

   int directMultiplier = 1;
   if (distanceInInches < 0)
   directMultiplier = -1;

   // double distanceInEncoders = distanceInInches * encoderPerInch;

   double current = 0;
   // double error = distanceInEncoders - current;
   double progress = current;
   double speed;

   // while ((fabs(error) > 10 ) && (millis() < maxTime))
   {
     current = (fl.get_position() + bl.get_position() + fr.get_position() +
		 br.get_position())/4;

     // error = distanceInEncodernbs - current;
     progress = current;
     // speed = minSpeed + accelerator * progress * error;

     double currentVelocity = fabs((fl.get_actual_velocity() +
		 fr.get_actual_velocity() + bl.get_actual_velocity() +
		 br.get_actual_velocity()) / 4);

     	if (speed > speedLimit) {
     		speed = speedLimit;
	 		}

     // deacceleration code
     // double maxDeaccelerationSpeed = 3.5 * sqrt(error);
//     if (currentVelocity > maxDeaccelerationSpeed)
  //   speed = maxDeaccelerationSpeed;

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

double get_angle() {
  /* We use the inertial sensor to get the angle of the robot. This is used in
  our turn funtion. */
//  double angle = inertial.get_heading();

  	// if (angle > 180) {
  	// 	angle = angle - 360;
  	// 	else if (angle <= -180)
  	// 	angle = 360 + angle;
  	// 	return angle;
}

/* void turn (double angle, int speed_limit) {
  bool not_at_target = true;

  // reset motors
  fl.tare_position();
  fr.tare_position();
  bl.tare_position();
  br.tare_position();

  double start_angle = get_angle();
  double target_angle = start_angle + angle;
  double start = 0;
  //double target = angle * encoder_per_degree_turn;
  double current = 0;
  double direction_multiplier = 1;
  int start_time = millis();
  int max_time = start_time + 20 * fabs(angle);

//  if (target < start)
  direction_multiplier = -1;
  while(not_at_target) {

    double current = (fl.get_position() - fr.get_position() - br.get_position() + bl.get_position())/4;
//    double error = (target - current);
    double progress = current - start;
    double speed = min_speed + 20 + fabs(accelerator * progress * error);
    double max_dec_speed = 4 * sqrt(error);

    double current_velocity = fabs((fl.get_actual_velocity() + fr.get_actual_velocity() + bl.get_actual_velocity() + br.get_actual_velocity()) / 4);

    if (current_velocity >max_dec_speed)
    speed = max_dec_speed;
    if (speed > speed_limit)
    speed = speed_limit;

    speed = speed*direction_multiplier;

    fl.move(speed);
    fr.move(-speed);
    bl.move( speed);
    br.move(-speed);

    double current_angle = get_angle();
    double error_angle = target_angle - current_angle;

    if (error_angle > 180)
    error_angle = error_angle - 360;
    else if (error_angle <= -180)
    error_angle = 360 + error_angle;
    if ( (fabs (error) < 10) || (fabs(error_angle) < 0.75) || (millis() > max_time) ) {

      fl.move(0);
      fr.move(0);
      bl.move(0);
      br.move(0);

      not_at_target = false;

      lcd::print(8, "error: %f", error);
      //  lcd::print(8, "error_angle: %f", error_angle);
    }
    delay (5);
  }
  delay(70); // let motors stop
}
*/

void liftFront() {
	frontLift.move(127);
}

void lowerFront() {
	frontLift.move(-127);
}

void liftLever() {
	lever.move(127);
}

void lowerLever() {
	lever.move(-127);
}

void liftBack() {
	backLift.move(127);
}

void lowerBack() {
	backLift.move(-127);
}

// fifteen second autonomous

// skills autonomous
