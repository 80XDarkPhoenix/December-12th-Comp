#include "main.h"

#include "math.h"

using namespace pros;

void rightSideAllianceGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing backwards
	move(-, 127); // reverse to alliance goal
	turn(45, 127); // turn to alliance goal
	move(-, 127); // reverse to touch alliance goal
	hookBackClaw(); // hook the back claw on alliance goal
	intakeRingIntake(); // start scoring preload rings on alliance goal
	move(, 127); // move alliance goal while scoring rings on it
}

void leftSideAllianceGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing left
	move(-, 127); // reverse to alliance goal
	hookBackClaw(); // hook the back claw on the alliance goal
	intakeRingIntake(); // start scoring preload rings on the alliance goal
	move(, 127); // move alliance goal while scoring rings on it
}

void rightSideAllianceGoalMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	move(-, 127); // reverse to alliance goal
	turn(-135, 127); // turn with the back facing the alliance goal
	move(-, 127); // reverse to alliance goal
	hookBackClaw(); // hook the back claw on the alliance goal
	intakeRingIntake(); // start scoring preload rings on the alliance goal
	move(, 127); // move goals while scoring preload rings on the alliance goal
}

void leftSideAllianceGoalMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(, 127); // move to mobile goal
	hookFrontClaw(); // hook front claw on mobile goal
	move(-, 127); // reverse to alliance goal
	turn(-90, 127); // turn so back faces the alliance goal
	move(-, 127); // reverse to alliance goal
	hookBackClaw(); // hook back claw on alliance goal
	intakeRingIntake(); // start scoring preload rings on the alliance goal
	move(, 127); // move goals while scoring preload rings on the alliance goal
}

void rightSideMobileGoalCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	move(, 127); // move to first mobile goal
	hookFrontClaw(); // hook front claw on first mobile goal
	move(, 127); // move to center of field
	turn(90, 127); // turn with back to center goal
	move(-, 127); // reverse to center goal
	hookBackClaw(); // hook back claw on center goal
	turn(45, 127); // turn with goals
	move(, 127); // move to alliance home zone scoring goals
}

void leftSideMobileGoalCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	move(, 127); // move to forst mobile goal
	hookFrontClaw(); // hook front claw on first mobile goal
	move(, 127); // move to center of the field
	turn(-90, 127); // turn with back to center goal
	move(-, 127); // reverse to center goal
	hookBackClaw(); // hook back claw on center goal
	turn(-45, 127); // turn with goals
	move(, 127); // move to alliamce home zone scoring goals
}

void rightSideMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	move(-, 127); // reverse to alliance zone
}

void leftSideMobileGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	// robot facing forward
	// move to mobile goal to get it before opposing alliance
	move(); // move to mobile goal
	hookFrontClaw(); // hook the front claw on the mobile goal
	move(-, 127); // reverse to alliance zone
}

void rightSideCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	move(, 127);
	turn(-45, 127); // turn to center goal
	move(, 127); // move to center goal
	hookFrontClaw(); // hook front claw on center goal
	move(-, 127); // reverse to alliance home zone with center goal
}

void leftSideCenterGoal() {
	unhookBackClaw();
	unhookFrontClaw();
	move(, 127);
	turn(45, 127); // turn to center goal
	move(, 127); // move to center goal
	hookFrontClaw(); // hool front claw on center goal
	move(-, 127); // reverse to alliane home zone with center goal
}
