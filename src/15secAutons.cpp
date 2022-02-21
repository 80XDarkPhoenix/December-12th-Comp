#include "main.h"
#include "math.h"

using namespace pros;

// mobile goal

void rightMobile() {
	frontLift.move_absolute(0, 50);
	move(48, 127, true); // move to mobile goal
	//moveLift(120); // lift lift so teams cannot steal the goal
	frontLift.move_absolute(150, 120);
	delay(200);
	move(-30, 127);
	frontLift.move_absolute(7, 120);
}

void leftMobile() {
	frontLift.move_absolute(0, 50);
	move(53, 127, true); // move to mobile goal
	//moveLift(120); // lift lift so teams cannot steal the goal
	frontLift.move_absolute(150, 120);
	delay(200);
	move(-36, 127);
	frontLift.move_absolute(7, 120);
}

// mobile and alliance goals

void rightMobileAlliance() {
	frontLift.move_absolute(-5, 10);
	move(48, 127, true); // move to mobile goal
	//moveLift(120); // lift lift so teams cannot steal the goal
	frontLift.move_absolute(150, 120);
	delay(500);
	move(-25, 127);
	frontLift.move_absolute(7, 120);

	delay(500);
	double currentAngle = getAngle();
	double turnAngle = -90-currentAngle;
	turn(turnAngle, 80);
	// turn with back to alliance goal
	 unhookBackClaw();
	move(-14, 80);
	hookBackClaw();
	delay(500);
	moveRingIntake(127);
	delay(4000);
	move(20, 80);
	unhookBackClaw();
}

void leftMobileAlliance() {
	frontLift.move_absolute(0, 50);
	move(53, 127, true); // move to mobile goal
	//moveLift(120); // lift lift so teams cannot steal the goal
	delay(400);
	move(-51, 120);
	frontLift.move_absolute(7, 120);
	turnTo(110, 80);
	frontLift.move_absolute(600, 120);
	delay(400);
	move(-16, 80);
	hookBackClaw();
	delay(400);
	moveRingIntake(127);
	move(36, 30);
	unhookBackClaw();
}

void rightAlliance() {}
void leftAlliance() {}

void leftWinPoint() {
	moveRingIntake(127);
	move(-2.5, 180);
	hookBackClaw();
	delay(400);
	move(5, 80);
	delay(200);
	turn(45, 80);
	move(5, 80);
	turn(55, 80);
	move(12, 80);
	turn(40, 80);
	move(16, 80);
  turn(70, 80);
  frontLift.move_absolute(500, 120);
  move(90, 50);
	unhookBackClaw();
	move(5, 80);
	turn(90, 80);
	move(12, 80);
	turn(90, 80);
  move(-15, 80);
	hookBackClaw();
	move(10, 80);
	turn(-90, 80);
	move(15, 50);
}

void winPoint() {
	move(-2.5, 80);
	hookBackClaw();
	delay(200);
	moveRingIntake(127);
	delay(2000);
	moveRingIntake(0);
	unhookBackClaw();
	move(10, 80);
	delay(200);
	turn(90, 80);
	delay(400);
	move(24, 80);
	delay(400);
	turn(-85, 80);
	delay(400);
	move(-115, 80);
	delay(400);
	hookBackClaw();
	delay(400);
	moveRingIntake(127);
	frontLift.move_absolute(600, 120);
	move(15, 80);
	delay(400);
	turn(-90, 80);
	delay(200);
	move(20, 40);
	/* hookBackClaw();
	delay(200);
	move(15, 80);
	delay(200);
	turn(-90, 80);
	delay(200);
	move(20, 50); */
}

void winPoint1() {
	move(-2.5, 80);
	hookBackClaw();
	delay(200);
	moveRingIntake(127);
	delay(2000);
	moveRingIntake(0);
	unhookBackClaw();
	move(10, 80);
	delay(200);
	turnTo(90, 80);
	delay(400);
	move(24, 80);
	delay(400);
	turnTo(0, 80);
	delay(400);
	move(-115, 80);
	turnTo(0, 80);
	delay(400);
	hookBackClaw();
	delay(400);
	moveRingIntake(127);
	frontLift.move_absolute(600, 120);
	move(15, 80);
	delay(400);
	turnTo(-90, 80);
	delay(200);
	move(36, 50);
}

void rightWinPoint() {
	move(-24, 80);
	hookBackClaw();
	move(-6, 80);
	turn(90, 80);
	frontLift.move_absolute(500, 120);
	moveRingIntake(127);
	move(80, 50);


}

void rightCenter() {
	frontLift.move_absolute(-5, 50);
	delay(1000);
	move(80, 127, true); // move to mobile goal
	delay(200);
	move(-60, 127);
}
void leftCenter() {}

void rightMobileCenter() {}
void leftMobileCenter() {}

void rightMobileCenterAlliance() {}
void leftMobileCenterAlliance() {}
