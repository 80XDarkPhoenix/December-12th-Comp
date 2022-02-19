#include "main.h"
#include "math.h"

using namespace pros;

// mobile goal

void rightMobile() {
	frontLift.move_absolute(0, 50);
	move(48, 127, true); // move to mobile goal
	//moveLift(120); // lift lift so teams cannot steal the goal
	frontLift.move_absolute(500, 120);
	move(-30, 127);
	frontLift.move_absolute(7, 120);
}

void leftMobile() {
	frontLift.move_absolute(0, 50);
	move(53, 127, true); // move to mobile goal
	//moveLift(120); // lift lift so teams cannot steal the goal
	frontLift.move_absolute(500, 120);
	delay(200);
	move(-30, 127);
	frontLift.move_absolute(7, 120);
}

// mobile and alliance goals

void rightMobileAlliance() {
	frontLift.move_absolute(0, 50);
	move(48, 127, true); // move to mobile goal
	//moveLift(120); // lift lift so teams cannot steal the goal
	frontLift.move_absolute(500, 120);
	delay(200);
	move(-24, 127);
	frontLift.move_absolute(7, 120);

	delay(200);
	turn(-90, 80); // turn with back to alliance goal
	move(-16, 80);
	hookBackClaw();
	delay(200);
	moveRingIntake(100);
	move(20, 127);
	unhookBackClaw();
	unhookFrontClaw();
}

void leftMobileAlliance() {
	// same thing as mobile goal

	unhookFrontClaw(); // let go of mobile goal in alliance zone
	delay(200);
	turn(-90, 100); // turn with back to alliance goal
	delay(200);
	move(-1, 100); // reverse to alliance goal
	hookBackClaw();
	delay(200);
	moveRingIntake(1);
}

void rightAlliance() {}
void leftAlliance() {}

void rightWinPoint() {}
void leftWinPoint() {}

void rightCenter() {}
void leftCenter() {}

void rightMobileCenter() {}
void leftMobileCenter() {}

void rightMobileCenterAlliance() {}
void leftMobileCenterAlliance() {}
