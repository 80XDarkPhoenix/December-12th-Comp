#include "main.h"
#include "math.h"

using namespace pros;

// mobile goal

void rightMobile() {
	// unhook both claws
	unhookFrontClaw();
	unhookBackClaw();

	move(, 127, true); // move to mobile goal
	moveLift(127); // lift lift so teams cannot steal the goal
	delay(400);
	moveLift(0); // stop lift

	move(-, 127); // move to alliance zone
}

void leftMobile() {
	// unhook both claws
	unhookFrontClaw();
	unhookBackClaw();

	move(, 127, true); // move to mobile goal
	moveLift(127); // lift lift so teams cannot steal the goal
	delay(400);
	moveLift(0); // stop lift

	move(-, 127); // move to alliance zone
}

// mobile and alliance goals

void rightMobileAlliance() {
	// same thing as mobile goal

	unhookFrontClaw(); // let go of mobile goal in alliance zone
	delay(200);
	turn(-90, 100); // turn with back to alliance goal
	move(-, 100);
	hookBackClaw();
	delay(200);
	moveRingIntake();
	move(, 127);
}

void leftMobileAlliance() {
	// same thing as mobile goal

	unhookFrontClaw(); // let go of mobile goal in alliance zone
	delay(200);
	turn(-90, 100); // turn with back to alliance goal
	delay(200);
	move(-, 100); // reverse to alliance goal
	hookBackClaw();
	delay(200);
	moveRingIntake();
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
