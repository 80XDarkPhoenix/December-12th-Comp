#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#include "api.h"
using namespace pros;

#ifdef __cplusplus
extern "C" {
#endif
  extern Motor fr;
  extern Motor fl;
  extern Motor br;
  extern Motor bl;

  extern Motor frontLiftLeft;
  extern Motor frontLiftRight;
  extern Motor backLiftLeft;
  extern Motor backLiftRight;

  extern ADIDigitalOut claw;

  extern Controller master;
  extern Controller partner;

  extern Imu inertial;

  void autonomous();
  void initialize();
  void disabled();
  void competition_initialize();
  void opcontrol();

  extern void drive();
  extern void driveFrontLift();
  extern void driveBackLift();
  extern void driveClaw();

  extern const double encoderPerInch;
  extern const double encoderPerDegreeTurn;

  extern const double defaultSpeed;
  extern const double defaultTurnSpeed;

  extern double minSpeed;
  extern double maxSpeed;

  extern double accelerator;

  extern void move(double distanceInInches, double speedLimit);

  extern int startTime;
  extern int maxTime;

  extern int directMultiplier;

  extern double distanceInEncoders;

  extern double current;
  extern double error;
  extern double progress;
  extern double speed;

	extern double currentVelocity;

  extern double maxDeaccelerationSpeed;

  extern double getAngle();
  extern double angle;

  extern void turn(double angle, int speedLimit);

  extern bool notAtTarget;

  extern double startAngle;
  extern double targetAngle;
  extern double start;
  extern double target;
  extern double current;
  extern double directionMultiplier;
  extern int startTime;
  extern int maxTime;

  extern double current;

  extern double error;
	extern double progress;
  extern double speed;
  extern double maxDeaccelerationSpeed;

	extern double currentVelocity;

	extern double currentAngle;
  extern double errorAngle;

  extern void liftFrontLift();
  extern void lowerFrontLift();

  extern void liftBackLift();
  extern void lowerBackLift();

  extern void unhookClaw();
  extern void hookClaw();

  extern void fifteenSecondAutonomousRightSideOneTower();
  extern void fifteenSecondAutonomousRightSideOneTowerMoveBack();
  extern void fifteenSecondAutonomousLeftSideOneTower();
  extern void fifteenSecondAutonomousRightSideTwoTowers();
  extern void fifteenSecondAutonomousRightSideCenterTower();
  extern void fifteenSecondAutonomousLeftSideTwoTowers();
  extern void fifteenSecondAutonomousLeftSideCenterTower();

  extern void calibrateMotor();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#endif
#endif
