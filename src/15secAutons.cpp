#include "main.h"
#include "math.h"

using namespace pros;

// CHANGE AND CHANGE PNEUMATICS DELAY AND LIFT AFTER PICKING UP 

/*
right mobile goal
left mobile goal
right mobile goal and alliance goal wp
left mobile goal and alliance goal wp
right alliance goal wp
left alliance goal wp
wp from right
wp from left
*/

// scores mobile goal and clears and scores rings in alliance goal on right side
void rightMobileGoalAllianceGoal() {
	// make sure claws are up
	unhookBackClaw();
	unhookFrontClaw();
	moveRingIntake(100);
	move(48, 127, true); // move to mobile goal
	//hookFrontClaw();
	delay(500);
	move(-20, 120);
	liftLift();
	delay(75);
	turn(-100, 120);
	moveLift(-127);
	delay(100);
	unhookFrontClaw();
	delay(200);
	move(-24, 120);
	hookBackClaw();
	delay(500);
	move(12, 120);
	delay(200);
	turn(-125, 120);
	liftLift();
	move(20, 100);
	delay(50);
	moveLift(0);

	unhookBackClaw();
	unhookFrontClaw();
}

/* scores mobile goal and center goal and clears and scores rings in alliance
goal on right side */
void rightMobileGoalCenterGoalAllianceGoal() {
	// make sure claws are unhooked
	unhookBackClaw();
	unhookFrontClaw();

	// move and hook claw on mobile goal
	move(-55, 127); // move to mobile goal
	hookBackClaw();
	delay(500);

	turn(97, 100);
	delay(200);
	move(28, 120);
	hookFrontClaw();
	delay(500);

	turn(60, 120);
	delay(200);
	move(-50, 120);
	delay(200);
	turn(45, 120);
	delay(200);
	move(-5, 120);
	unhookBackClaw();
	delay(200);

	move(7, 120);
	delay(200);
	turn(-90, 120);
	hookBackClaw();
	moveRingIntake(100);
	delay(200);

	move(-12, 120);

	unhookBackClaw();
	unhookFrontClaw();
}

// scores mobile goal and clears and scores rings in alliance goal on left side
void leftMobileGoalAllianceGoal() {
	// make sure claws are unhooked
	unhookBackClaw();
	unhookFrontClaw();

	// move and hook claw on mobile goal

	move(48, 127, true); // move to mobile goal
	// hookFrontClaw();
	delay(500);

	move(-52, 110); // reverse to alliance zone
//	backDistanceMove(); // correct distance

// let go of mobile go (in home zone)
	unhookFrontClaw();
	delay(200);

	turn(-120, 80); // turn with back to center goal
	moveLift(110);
	delay(100);
	move(-13, 80);
	moveLift(0);
	hookBackClaw();
	delay(250);
	moveRingIntake(100);
	move(35, 40);
	delay(100);
	move(-15, 50);
	delay(200);
	move(15, 50);
	delay(200);
	move(-15, 50);
	delay(200);
	move(15, 50);
	delay(200);
	move(-15, 50);
	delay(200);
	move(15, 50);

	unhookBackClaw();
	unhookFrontClaw();
}
