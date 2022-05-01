#include "main.h"
#include "math.h"

void rMobileAlliance() {
  transmission.set_value(0); // switch to speed mode
  claw.set_value(1); // bring clamp up
  moveFast(39.0, 127, true); // move towards and clamp on mobile goal
  transmission.set_value(1); // switch to torque mode
  moveBack(-30, 100); // reverse to home zone at slow speed to pull at 0 degrees
  turnTo(-90, 100);
}

void rMobile1() {
  transmission.set_value(0); // switch to speed mode
  claw.set_value(1); // bring clamp up
  moveFast(39.0, 127, true); // move towards and clamp on mobile goal
  transmission.set_value(1); // switch to torque mode
  moveBack(-30, 100); // reverse to home zone at slow speed to pull at 0 degrees
} // end of rMobile

void lMobile() {
  claw.set_value(1); // bring clamp up
  moveFast(39.0, 127, true); // move towards and clamp on mobile goal
  transmission.set_value(0); // switch to torque mode
  moveBack(-30, 100); // reverse to home zone at slow speed to pull at 0 degrees
} // end of lMobile

void rCenter() {

} // end of rCenter

void lCenter() {

} // end of lCenter

void rAlliance() {
  // starts backwards
  // make sure both clamps are up
  unhookClaw();
  unhookTilter();

  move(-0, 80); // reverse towards alliance goal
  turn(45, 80); // turn with back facing alliance goal
  move(-0, 80); // reverse to alliance goal
  hookTilter(); // hook back onto alliance goal
  delay(0);
  moveRingIntake(127); // start ring intake to score preloads
  move(0, 80); // clear alliance goal
  turn(180, 80);
  // turn with back facing perimeter preventing teams from getting the goal
  unhookTilter(); // let go of alliance goal
  moveRingIntake(0); // stop ring intake
}

void lAlliance() {
  // make sure both clamps are up
  unhookClaw();
  unhookTilter();

  move(-0, 80);
  delay(0);
  hookTilter();
  delay(0);
  moveRingIntake(127);
  move(0, 100);
  unhookTilter();
  moveRingIntake(0);
}

void rAllianceRings() {
  // starts backwards
  // make sure both clamps are up
  unhookClaw();
  unhookTilter();

  move(-0, 80); // reverse towards alliance goal
  turn(45, 80); // turn with back facing alliance goal
  move(-0, 80); // reverse to alliance goal
  hookTilter(); // hook back onto alliance goal
  delay(0);
  moveRingIntake(127); // start ring intake to score preloads
  turnTo(135, 80);
  move(0, 80); // move to white line
  turnTo(90, 80);
  move(0, 80);
  move(-0, 80);
  turnTo(135, 80);
  move(-0, 80);
  unhookTilter();
  moveRingIntake(0);
}

void lAllianceRings() {}

void rMobileAllianceRings() {
  // make sure both clamps are up
  unhookClaw();
  unhookTilter();

  move(0, 127);
  hookClaw();
  move(-0, 127);
  turnTo(-90, 100);
  move(-0, 100);
  hookTilter();
  delay(0);
  moveRingIntake(127);
  move(0, 0);
  moveLift(100);
  turnTo(0, 100);
  move(0, 0);
  turnTo(90, 100);
  moveLift(0);
  move(0, 100);
  move(-0, 100);
  unhookTilter();
  moveRingIntake(0);
}

void lMobileAllianceRings() {
  // starts at a slight angle
  // make sure both clamps are up
  unhookClaw();
  unhookTilter();

  move(0, 127);
  hookClaw();
  move(-0, 127);
  turnTo(-45, 80);
  move(-0, 80);
  hookTilter();
  delay(0);
  moveRingIntake(127);
  move(0, 80);
  turnTo(-90, 80);
  move(0, 80);
  move(-0, 80);
  unhookTilter();
  moveRingIntake(0);
}

void rWP() {}
void lWP() {}

void rMobileCenter() {}
void lMobileCenter() {}

void rCenterAlliance() {}
void lCenterAlliance() {}

// void rMobileAlliance() {}
void lMobileAlliance() {}

void rMobileAllianceCenter() {}
void lMobileAllianceCenter() {}

/* OLD AUTONS

void rightMobileFast() {
	unhookFrontClaw();
	unhookBackClaw();

	frontLift.move_absolute(-5, 50); // checks to make sure lift is down
	move(48, 127, true); // moves to mobile goal while hooking front claw
	delay(200); // wait for the front claw to hook on the goal
	move(-200, 127);
	// Reverses to alliance zone at a large value tp ensure we get the goal when
	// another team is hooked on at the same time as us.
}

void leftMobileFast() {
	unhookFrontClaw();
	unhookBackClaw();

	// robot starts at slight angle due to the obstructing alliance goal
	frontLift.move_absolute(-5, 50); // checks to make sure lift is down
	move(53, 127, true); // moves to mobile goal while hooking front claw
	delay(200); // wait for the front claw to hook on the goal
	move(-200, 127);
	// Reverses to alliance zone at a large value tp ensure we get the goal when
	// another team is hooked on at the same time as us.
}

void rightMobileAlliance() {
	unhookFrontClaw();
	unhookBackClaw();

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
	unhookFrontClaw();
	unhookBackClaw();

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
	move(36, 80); // moves towards drivers box for match loads
	unhookBackClaw(); // let go of alliance goal
}

void winPoint() {
	unhookFrontClaw();
	unhookBackClaw();

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
	unhookBackClaw();
}

void rightCenter() {
	unhookFrontClaw();
	unhookBackClaw();

	frontLift.move_absolute(-5, 127);
	move(74, 127);
	hookFrontClaw();
	delay(200);
	move(-60, 127);
}

void igneous() {
	unhookFrontClaw();
	unhookBackClaw();

	frontLift.move_absolute(-5, 127);
	move(74, 127);
	hookFrontClaw();
	delay(200);
	move(-60, 127);
}

*/
