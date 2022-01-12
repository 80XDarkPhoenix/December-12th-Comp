#include "main.h"
#include "math.h"

using namespace pros;

void rightSideAllianceGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing backwards
	// move(-, 110); // reverse to alliance goal
	turn(45, 110); // turn to alliance goal
	// move(-, 110); // reverse to touch alliance goal
	hookBackClaw(); // hook the back claw on alliance goal
	intakeRingIntake(); // start scoring preload rings on alliance goal
	// move(, 110); // move alliance goal while scoring rings on it
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

void rightSideAllianceGoalMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	// move(); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	// move(-, 110); // reverse to alliance goal
	turn(-135, 110); // turn with the back facing the alliance goal
	// move(-, 110); // reverse to alliance goal
	hookBackClaw(); // hook the back claw on the alliance goal
	intakeRingIntake(); // start scoring preload rings on the alliance goal
	// move(, 110); // move goals while scoring preload rings on the alliance goal
}

void leftSideAllianceGoalMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	// move(, 110); // move to mobile goal
	hookFrontClaw(); // hook front claw on mobile goal
	// move(-, 110); // reverse to alliance goal
	turn(-90, 110); // turn so back faces the alliance goal
	// move(-, 110); // reverse to alliance goal
	hookBackClaw(); // hook back claw on alliance goal
	intakeRingIntake(); // start scoring preload rings on the alliance goal
	// move(, 110); // move goals while scoring preload rings on the alliance goal
}

void rightSideMobileGoalCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// move(, 110); // move to first mobile goal
	hookFrontClaw(); // hook front claw on first mobile goal
	// move(, 110); // move to center of field
	turn(90, 110); // turn with back to center goal
	// move(-, 110); // reverse to center goal
	hookBackClaw(); // hook back claw on center goal
	turn(45, 110); // turn with goals
	// move(, 110); // move to alliance home zone scoring goals
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
	move(50, 110); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
//	move(-, 110); // reverse to alliance zone
}

void leftSideMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	// move(, 110); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	// move(-, 110); // reverse to alliance zone
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
