#include "main.h"
#include "math.h"

using namespace pros;

void rightSideAllianceGoalMobileGoal() {
	// make sure claws are unhooked
	unhookBackClaw();
	unhookFrontClaw();

	// move and hook claw on mobile goal
	move(55, 127);
	hookFrontClaw();
	delay(500);

	move(-32, 80); // reverse to alliance zone

	// let go of mobile go (in home zone)
	unhookBackClaw();
	delay(200);
	unhookFrontClaw();

	turn(-135, 80); // turn with back to center goal
	delay(200);
	moveLift(110);

	// clear and put rings on alliance goal
	move(-20, 80); // reverse to center goal
	moveLift(0);
	moveRingIntake(100);
	delay(3000);
	move(5, 127);
}

void leftSideAllianceGoal() {
	// make sure rings
	unhookBackClaw();
	unhookFrontClaw();

	// put ring on alliance goal
	hookFrontClaw();
	delay(2000);
	unhookFrontClaw();
	move(-13, 80);
}
