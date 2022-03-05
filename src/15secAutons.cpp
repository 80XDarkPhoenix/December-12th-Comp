#include "main.h"
#include "math.h"

using namespace pros;

void rightMobileFast() {
	frontLift.move_absolute(-5, 50); // checks to make sure lift is down
	move(48, 127, true); // moves to mobile goal while hooking front claw
	delay(200); // wait for the front claw to hook on the goal
	move(-200, 127);
	/* Reverses to alliance zone at a large value tp ensure we get the goal when
	another team is hooked on at the same time as us. */
}

void leftMobileFast() {
	// robot starts at slight angle due to the obstructing alliance goal
	frontLift.move_absolute(-5, 50); // checks to make sure lift is down
	move(53, 127, true); // moves to mobile goal while hooking front claw
	delay(200); // wait for the front claw to hook on the goal
	move(-200, 127);
	/* Reverses to alliance zone at a large value tp ensure we get the goal when
	another team is hooked on at the same time as us. */
}

void rightMobileAlliance() {
	frontLift.move_absolute(-5, 50); // checks to make sure lift is down
	move(48, 127, true); // moves to mobile goal while hooking front claw
	delay(200); // wait for the front claw to hook on the goal
	move(-25, 127); // reverse to alliance zone

	delay(400);
	turnTo(-90, 80); // turn facing the alliance goal
	unhookBackClaw();
	delay(200);
	move(-14, 80); // reverses to alliance goal
	hookBackClaw(); // hooks back claw on alliance goal
	delay(200); // wait for the back claw to hook on the goal
	moveRingIntake(127); // starts the ring intake
	delay(4000); // wait to score rings on alliance goal
	move(20, 80); // clear alliance goal
	unhookBackClaw(); // let go of alliance goal
}

void leftMobileAlliance() {
	frontLift.move_absolute(-5, 50); // checks to make sure lift is down
	move(53, 127, true); // moves to mobile goal while hooking front claw
	delay(200); // wait for the front claw to hook on the goal
	move(-40, 127); // reverse to alliance zone
	delay(400);
	turnTo(-110, 80); // turn facing the alliance goal
	delay(400);
	move(-16, 80); // reverse to alliance goal
	hookBackClaw(); // hooks back claw on alliance goal
	frontLift.move_absolute(1300, 100); // lifts the lift for the ring intake
	delay(400);
	moveRingIntake(127); // starts ring intake
	move(36, 30); // moves towards drivers box for match loads
	unhookBackClaw(); // let go of alliance goal
}

void winPoint() {
	// starts with back facing left alliance goal
	move(-2.5, 80); // reverses to alliance goal
	hookBackClaw(); // hooks back claw on alliance goal
	delay(200); // wait for the front claw to hook on the goal
	moveRingIntake(127); // starts ring intake
	delay(2000); // wait to score rings on alliance goal
	moveRingIntake(0); // stops ring intake
	unhookBackClaw(); // lets go of alliance goal
	move(10, 80);
	delay(400);
	turnTo(90, 80);
	delay(400);
	move(20, 80);
	delay(200);
	turnTo(90, 80);
	delay(200);
	turnTo(0, 80);
	delay(200);
	turnTo(0, 80);
	delay(400);
	// back facing the right alliance goal
	move(-115, 80); // reverses to right alliance goal
	delay(200);
	hookBackClaw(); // hooks back claw on alliance goal
	delay(400);
	moveRingIntake(127); // starts ring intake
	frontLift.move_absolute(600, 120); // lifts lift
	move(15, 80); // clears alliance goal
	delay(400);
	turnTo(-90, 80); // turns facing drivers box
	delay(200);
	move(36, 80); // moves towards drivers box for match loads
}

void rightCenter() {
	frontLift.move_absolute(-5, 127);
	move(74, 127);
	hookFrontClaw();
	delay(200);
	move(-60, 127);
}
