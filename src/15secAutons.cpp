#include "main.h"
#include "math.h"

using namespace pros;

void rightSideAllianceGoalMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	move(55, 127); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	delay(500);
	move(-32, 80); // reverse to alliance zone

	unhookBackClaw();
	delay(200);
	unhookFrontClaw();
	turn(-135, 80); // turn with back to center goal
	delay(200);
	moveLift(110);
	move(-20, 80); // reverse to center goal
	moveLift(0);
	moveRingIntake(100);
	delay(3000);
	move(5, 127);
}

void leftSideAllianceGoalMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();

	hookFrontClaw();
	delay(2000);
	unhookFrontClaw();
	move(-13, 80);
/*	delay(200);
	turn(-50, 80);
	delay(200);
	move(72, 80);
	delay(100);
	hookFrontClaw();
	delay(500);
	move(-35, 80);
	unhookFrontClaw(); */
}



////////////////////////////////////////////////////////////////////////////////

/*
void rightSideAllianceGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing backwards at 45 degree angle
	move(-22, 110); // reverse to alliance goal
	hookBackClaw(); // hook the back claw on alliance goal
	intakeRingIntake(); // start scoring preload rings on alliance goal
	move(5, 110); // move alliance goal while scoring rings on it
}

void leftSideAllianceGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing left
	// move(-, 110); // reverse to alliance goal
	hookBackClaw(); // hook the back claw on the alliance goal
	intakeRingIntake(); // start scoring preload rings on the alliance goal
	// move(, 110); // move alliance goal while scoring rings on it
}

void rightSideMobileGoalCenterGoal() {
}

void leftSideMobileGoalCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// move(, 110); // move to forst mobile goal
	hookFrontClaw(); // hook front claw on first mobile goal
	// move(, 110); // move to center of the field
	turn(-90, 110); // turn with back to center goal
	// move(-, 110); // reverse to center goal
	hookBackClaw(); // hook back claw on center goal
	turn(-45, 110); // turn with goals
	// move(, 110); // move to alliamce home zone scoring goals
}

void rightSideMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(55, 110); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	delay(500);
  move(-30, 110); // reverse to alliance zone
}

void mobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(55, 110); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	delay(500);
  move(-30, 110); // reverse to alliance zone
}

void rightSideCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// move(, 110);
	turn(-45, 110); // turn to center goal
	// move(, 110); // move to center goal
	hookFrontClaw(); // hook front claw on center goal
	// move(-, 110); // reverse to alliance home zone with center goal
}

void leftSideCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// move(, 110);
	turn(45, 110); // turn to center goal
	// move(, 110); // move to center goal
	hookFrontClaw(); // hool front claw on center goal
	// move(-, 110); // reverse to alliane home zone with center goal
}

*/
