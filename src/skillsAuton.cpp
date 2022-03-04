#include "main.h"
#include "math.h"

using namespace pros;

void skills() {
  // make sure claws are up
  unhookBackClaw();
  unhookFrontClaw();

  move(-7, 80); // reverse to alliance goal
  hookBackClaw(); // hook onto alliance goal
  delay(200); // wait to fully hook on
  // hooked red alliance goal with back claw

  move(12, 80); // leave platform
  moveRingIntake(127); // start ring intake to score preloads
  delay(200);
  turnTo(45, 80);
  delay(200);
  move(12, 80);
  delay(200);
  turnTo(90, 80);
  delay(200);
  move(24, 80);
  delay(200);
  turnTo(127, 80); // position robot to hook onto mobile goal
  delay(200);
  move(24, 80, true); // hook onto mobile goal
  // hooked onto mobile goal

  delay(200); // wait to fully hook onto mobile goal
  moveLift(127); // move lift up
  delay(1500);
  moveLift(0); // stop lift
  move(63, 60); // move to platform at slow speed to prevent jerking
  delay(600);
  turnTo(90, 80); // turn to face platform
  delay(200);
  move(5, 80); // go into platform
  moveLift(-127); // lower lift
  delay(300);
  moveLift(0); // stop lift
  unhookFrontClaw(); // unhook mobile goal on platform
  frontLift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  // stack mobile goal

  move(-10, 80); // reverse from platform
  frontLift.move_absolute(-5, 127); // lower lift to ground
  delay(100);
  turnTo(90, 80); // correct turn
  delay(100);
  unhookBackClaw(); // let go of alliance goal
  delay(200);
  move(-10, 80); // push alliance goal back
  delay(200);
  move(7, 80); // move away alliance goal
  delay(200);
  turnTo(-90, 80); // turn to face alliance goal
  delay(200);
  move(11, 80, true); // hook onto alliance goal
  delay(200);
  turnTo(0, 40); // turn to reverse
  delay(200);
  move(-13, 80); // reverse to right position for platform
  frontLift.move_absolute(1450, 127); // lift the lift
  delay(200);
  turnTo(90, 40); // turn to face platform at slow speed for accuracy
  delay(200);
  move(20, 80); // move into platform
  moveLift(-127); // lower lift into platform
  delay(300);
  moveLift(0); // stop lift
  unhookFrontClaw(); // unhook alliance goal
  // stack alliance goal

  frontLift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  move(-5, 80); // reverse from platform
  frontLift.move_absolute(-5, 127); // lower lift to ground
  move(-15, 80); // reverse from platform
  delay(200);
  turnTo(100, 60); // turn to center goal at slow speed for accuracy
  delay(200);
  move(-20, 80); // reverse to center goal
  delay(200);
  hookBackClaw(); // hook onto center goal
  delay(200);

  move(-30, 80); // move center to alliance zone
  delay(200);
  turnTo(180, 80); // turn to alliance goal
  delay(200);
  unhookBackClaw(); // let go of center goal
  move(33, 80); // move to alliance goal
  delay(400);
  turnTo(0, 40); // turn with back facing alliance goal
  delay(400);
  turnTo(0, 40); // correct turn
  delay(400);
  move(-20, 80); // reverse against alliance goal
  delay(200);
  hookBackClaw(); // hook onto alliance goal

  delay(200);
  move(15, 200); // move away from wall
  delay(200);
  turnTo(90, 80); // turn to mobile goal
  delay(200);
  move(40, 80, true); // hook onto mobile goal
  delay(200);
  frontLift.move_absolute(1450, 127); // lift the lift
  turnTo(45, 80); // turn to desired stacking position
  delay(200);
  move(40, 80); // move to platform
  delay(200);
  turnTo(0, 80); // turn to platform
  delay(200);
  move(10, 80); // move to desired position
  delay(200);
  turnTo(90, 80); // turn to platform
  delay(200);
  move(12, 80); // move into platform
  delay(200);
  moveLift(-127); // lower lift
  delay(300);
  moveLift(0); // stop life=t
  unhookFrontClaw(); // stack mobile goal

  delay(200);
  frontLift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  move(-5, 80); // reverse from platform
  frontLift.move_absolute(-5, 127); // lower lift to the grounf
  delay(200);
  move(-5, 80); // reverse from platform
  delay(200);
  turnTo(90, 80); // correct turn
  delay(200);
  move(-10, 80); // reverse from platform
  unhookBackClaw(); // unhook alliance goal
  delay(200);
  move(7, 80); // move away from alliance goal
  delay(200);
  turnTo(-90, 80); // turn to alliance goal
  delay(200);
  turnTo(-90, 80); // correct turn
  delay(200);
  move(12, 80, true); // hook onto alliance goal
  delay(200);
  frontLift.move_absolute(1450, 127); // lift the lift
  turnTo(90, 80); // turn to platform
  delay(200);
  move(32, 80); // move into platform
  delay(200);
  moveLift(-127); // lower lift
  delay(300);
  moveLift(0); // stop lift
  delay(200);
  move(5, 80); // move more into platform to stack in correct position
  delay(200);
  unhookFrontClaw(); // stack alliance goal

  delay(200);
  move(-8, 80); // reverse from platform
  frontLift.move_absolute(-5, 127); // lower lift to ground
  delay(200);
  turnTo(180, 80); // turn with back to alliance goal
  delay(200);
  turnTo(180, 80); // correct turn
  delay(200);
  move(-65, 80); // reverse to alliance goal
  delay(200);
  hookBackClaw(); // hook onto alliancw goal
  delay(400);
  move(120, 80); // move to other alliance goal



/*  // turnTo(180, 80);
  // delay(400);
  move(-66, 80);
  delay(200);
  turnTo(180, 80);
  delay(400);
  hookBackClaw(); // hook onto alliance goal

  delay(200);
  turnTo(205, 80);
  move(50, 80, true);
  delay(200);
  move(80, 80);
  unhookFrontClaw(); */

}
