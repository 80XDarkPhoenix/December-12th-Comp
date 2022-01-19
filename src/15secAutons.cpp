#include "main.h"
#include "math.h"

using namespace pros;

void leftAllianceGoal() {
	// make sure claws are up
	unhookBackClaw();
	unhookFrontClaw();

	// put ring on alliance goal
	hookFrontClaw();
	delay(2000);
	unhookFrontClaw();
	move(-13, 127);
}

// done
void rightAllianceGoal() {
	// make sure claws are up
	unhookBackClaw();
	unhookFrontClaw();

	// start backwards at an angle
	moveLift(127);
	move(-27, 90); // move to/clear alliance goal
	moveLift(0);
	moveRingIntake(100); // start ring intake
	delay(5000); // score rings on alliance goal
	moveRingIntake(0); // stop ring intake
	move(10, 127); // move from alliance goal
}

// done
void rightMobileGoalAllianceGoal() {
	// make sure claws are unhooked
	unhookBackClaw();
	unhookFrontClaw();

	// move and hook claw on mobile goal
	move(55, 127); // move to mobile goal
	hookFrontClaw();
	delay(500);

	move(-32, 110); // reverse to alliance zone
//	backDistanceMove(); // correct distance

	// let go of mobile go (in home zone)
	unhookBackClaw();
	delay(200);
	unhookFrontClaw();

	turn(-140, 80); // turn with back to center goal
	delay(200);
	moveLift(110);

	// clear and put rings on alliance goal
	move(-20, 80); // reverse to center goal
	moveLift(0);
	moveRingIntake(100);
	delay(3000);
	moveRingIntake(0);
	move(5, 127);
}

void rightMobileGoalCenterGoalAllianceGoal() {
	// make sure claws are unhooked
	unhookBackClaw();
	unhookFrontClaw();

	// move and hook claw on mobile goal
	move(-55, 127); // move to mobile goal
	hookBackClaw();
	delay(500);

	move(32, 127); // reverse to alliance zone
	// backDistanceMove(); // correct distance

	delay(50);
	turn(145, 127); // turn with back to center goal
	delay(50);

	move(38, 127);
	hookFrontClaw();
	delay(500);

	move(-42, 120);
	delay(50);
	turn(90, 120);
	unhookBackClaw();
	delay(200);
	move(-7, 120);
	delay(50);
	turn(-145, 120);
	unhookFrontClaw();
	delay(50);
	moveLift(127);
	move(-8, 120);
	moveLift(0);
	moveRingIntake(100);
	delay(2000);
	moveRingIntake(0);
	move(10, 127);

/*	// let go of mobile go (in home zone)
	unhookBackClaw();
	delay(200);
	unhookFrontClaw();

	moveLift(110);

	// clear and put rings on alliance goal
	move(-20, 80); // reverse to center goal
	moveLift(0);
	moveRingIntake(100);
	delay(3000);
	moveRingIntake(0);
	move(5, 127); */
}

/*
void leftMobileGoalAllianceGoal() {
	// make sure claws are up
	unhookFrontClaw();
	unhookBackClaw();

	// move and hook claw on mobile goal
	move(, 127); // move to mobile goal
	hookFrontClaw();
	delay(500);

	move(-32, 80); // reverse to alliance zone
	delay(50);
	backDistanceMove(); // correct distance
	delay(50);
	unhookFrontClaw();
	turn(-90, 80);
	delay(50);

	// move to and score ring(s) on alliance goal
	move(-, 80);
	moveRingIntake(100);
	delay(3000);
	moveRingIntake(0);

	move(5, 127);
}

void rightAllianceGoals() {}

void leftAllianceGoals() {}

void rightAllianceGoalMobileGoals() {}

void leftAllianceGoalMobileGoals() {}
*/

void winPoint() {
	// make sure claws are unhooked
	unhookBackClaw();
	unhookFrontClaw();
	
	// move(distance, speed);
	// delay(50);
	// turn(angle, speed);
	// moveLift(speed);
	// moveRingIntake(speed);
	// hookBackClaw();
	// unhookBackClaw();
}
