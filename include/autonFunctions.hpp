#ifndef AUTONFUNCTIONS
#define AUTONFUNCTIONS

extern const double encoderPerInch;
extern const double encoderPerDegreeTurn;

// Speed
extern const double defaultSpeed;
extern const double defaultTurnSpeed;

extern double minSpeed;
extern double maxSpeed;

// Accelerator
extern double accelerator;
extern double turnAccelerator;

// Move
extern void move(double distanceInInches, double speedLimit);

// Turn
extern double getAngle();
extern void turn (double angle, int speedLimit);

// Lifts
extern void liftFrontLift();
extern void lowerFrontLift();
extern void moveLift(double liftSpeed);

// CLAWS

// front claw
extern void hookFrontClaw();
extern void unhookFrontClaw();

// back claw
extern void hookBackClaw();
extern void unhookBackClaw();

// ring intake
void moveRingIntake(double ringIntakeSpeed);

void calibrateMotor();
#endif
