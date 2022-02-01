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

	move(34, 110); // reverse to alliance zone
	// backDistanceMove(); // correct distance

	delay(50);
	turn(145, 100); // turn with back to center goal
	delay(50);

	move(42, 120);
	hookFrontClaw();
	delay(500);

	move(-40, 110);
	delay(50);
	turn(90, 110);
	unhookBackClaw();
	delay(500);
	move(-7, 110);
	delay(50);
	turn(-165, 110);
	unhookFrontClaw();
	delay(50);
	moveLift(127);
	move(-18, 110);
	moveLift(0);
	moveRingIntake(100);
	delay(2000);
	moveRingIntake(0);
	move(10, 127);
}

void leftMobileGoalAllianceGoal() {
	// make sure claws are unhooked
	unhookBackClaw();
	unhookFrontClaw();

	// move and hook claw on mobile goal
	move(60, 127); // move to mobile goal
	hookFrontClaw();
	delay(500);

	move(-52, 110); // reverse to alliance zone
//	backDistanceMove(); // correct distance

// let go of mobile go (in home zone)
	unhookFrontClaw();
	delay(200);

	turn(-120, 80); // turn with back to center goal
	moveLift(110);
	delay(50);
	move(-13, 80);
	moveLift(0);
	moveRingIntake(100);
	delay(3000);
	move(10, 100);
}

void leftWinPoint() {
	// start 90 degrees
	// make sure claws are unhooked
	unhookBackClaw();
	unhookFrontClaw();

	hookFrontClaw();
	delay(500);
	unhookFrontClaw();

	move(-10, 100);
	delay(50);
	turn(135, 100);

	move(-22, 100);
	delay(50);
	turn(65, 100);
	unhookBackClaw();
	move(-96, 100);

	hookBackClaw();
	delay(500);
	moveRingIntake(100);
	delay(2000);
	move(25, 127);
	moveRingIntake(0);
}
