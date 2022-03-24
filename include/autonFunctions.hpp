#ifndef AUTONFUNCTIONS
#define AUTONFUNCTIONS

extern const double encoderPerInch;
extern const double encoderPerDegreeTurn;

// speed
extern const double defaultSpeed;
extern const double defaultTurnSpeed;

extern double minSpeed;
extern double turnMinSpeed;
extern double maxSpeed;

// accelerator
extern double accelerator;
extern double turnAccelerator;
extern double maxDeaccelerationSpeed;
extern double deaccelFactor;
extern double turnDeaccelFactor;

extern void resetBaseMotors();
extern void stopBaseMotors();

// move
extern void move(double distanceInInches, double speedLimit, bool operateClaw = false);

// turn
extern double getAngle();
extern void turn (double angle, int speedLimit);
extern void turnTo(double angle, int speedLimit);

// lift
extern void liftLift();
extern void lowerLift();
extern void moveLift(double liftSpeed);

// claws

// front claw
extern void hookFrontClaw();
extern void unhookFrontClaw();

// back claw
extern void hookBackClaw();
extern void unhookBackClaw();

// ring intake
void moveRingIntake(double ringIntakeSpeed);

// distance
/*
double getFrontDistance();
double getBackDistance();

void frontDistanceMove(double goalDistanceFromWall);
void backDistanceMove(double goalDistanceFromWall);
*/
#endif
