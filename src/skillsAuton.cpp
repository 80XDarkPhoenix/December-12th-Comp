#include "main.h"
#include "math.h"

using namespace pros;

void riskSkills() {
  // make sure claws are up
  unhookBackClaw();
  unhookFrontClaw();

  move(-7, 80); // reverse to alliance goal
  hookBackClaw(); // hook onto alliance goal
  delay(200); // wait to fully hook on
  // hooked red alliance goal with back claw

  move(12, 80); //     leave platform
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
  move(80, 80, true); // hook onto mobile goal
  // hooked onto mobile goal

  delay(600); // wait to fully hook onto mobile goal
  moveLift(127); // move lift up
  delay(1500);
  moveLift(0); // stop lift
  delay(200);
  move(6, 80);
  delay(200);
  turnTo(90, 80); // turn to face platform
  delay(200);
  turnTo(90, 80);
  delay(200);
  move(10, 60); // go into platform
  delay(200);
  moveLift(-127); // lower lift
  delay(300);
  moveLift(0); // stop lift
  delay(200);
  unhookFrontClaw(); // unhook mobile goal on platform
  delay(400);
  frontLift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  // stack mobile goal

  move(-13, 80); // reverse from platform
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
  turnTo(0, 80); // turn to reverse
  delay(200);
  turnTo(0, 80); // correct turn
  delay(200);
  move(-20, 80); // reverse to right position for platform
  frontLift.move_absolute(1450, 127); // lift the lift
  delay(200);
  turnTo(90, 40); // turn to face platform at slow speed for accuracy
  delay(200);
  move(26, 80); // move into platform
  delay(200);
  moveLift(-127); // lower lift into platform
  delay(300);
  moveLift(0); // stop lift
  unhookFrontClaw(); // unhook alliance goal
  delay(400);
  // stack alliance goal

  frontLift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  move(-7, 80); // reverse from platform
  frontLift.move_absolute(-5, 127); // lower lift to ground
  move(-15, 80); // reverse from platform
  delay(200);
  turnTo(120, 60); // turn to center goal at slow speed for accuracy
  delay(200);
  move(-20, 80); // reverse to center goal
  delay(200);
  hookBackClaw(); // hook onto center goal
  delay(200);

  move(-44, 80); // move center to alliance zone
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
  move(-45, 80); // reverse against alliance goal
  delay(200);
  hookBackClaw(); // hook onto alliance goal

  delay(200);
  move(15, 200); // move away from wall
  delay(200);
  turnTo(90, 40); // turn to mobile goal
  delay(400);
  turnTo(90, 40);
  move(40, 80);
  hookFrontClaw(); // hook onto mobile goal
  delay(200);
  frontLift.move_absolute(1300, 127); // lift the lift
  turnTo(45, 80); // turn to desired stacking position
  delay(200);
  move(30, 80); // move to platform
  delay(200);
  turnTo(0, 80); // turn to platform
  delay(200);
  move(15, 80); // move to desired position
  delay(200);
  turnTo(90, 80); // turn to platform
  delay(200);
  move(30, 80); // move into platform
  delay(200);
  moveLift(-127); // lower lift
  delay(300);
  moveLift(0); // stop lift
  unhookFrontClaw(); // stack mobile goal

  delay(400);
  frontLift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  move(-7, 80); // reverse from platform
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
  move(16, 80);
  hookFrontClaw(); // hook onto alliance goal
  delay(200);
  move(-10, 80);
  frontLift.move_absolute(1300, 127); // lift the lift
  turnTo(90,40);
  delay(400);
  turnTo(90,40);
  move(22, 80); // move into platform
  delay(200);
  moveLift(-127); // lower lift
  delay(300);
  moveLift(0); // stop lift
  delay(200);
  move(5, 80); // move more into platform to stack in correct position
  delay(200);
  unhookFrontClaw(); // stack alliance goal

  move(-10, 80); // reverse from platform
  frontLift.move_absolute(-5, 127); // lower lift to ground
  delay(400);
  turnTo(0, 80);
  delay(200);
  turnTo(0, 80);
  delay(200);
  move(64, 80);
  delay(200);
  hookFrontClaw();
  delay(200);
  turnTo(-130, 80);
  delay(200);
  frontLift.move_absolute(1300, 127);
  move(100, 80);
  delay(200);
  unhookFrontClaw();
  delay(200);
  move(-20, 127);
}

void skills() {
  // make sure claws are up
  unhookBackClaw();
  unhookFrontClaw();

  move(-7, 80); // reverse to alliance goal
  hookBackClaw(); // hook onto alliance goal
  delay(200); // wait to fully hook on
  // hooked red alliance goal with back claw

  move(12, 80); //     leave platform
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
  move(80, 80, true); // hook onto mobile goal
  // hooked onto mobile goal

  delay(600); // wait to fully hook onto mobile goal
  moveLift(127); // move lift up
  delay(1500);
  moveLift(0); // stop lift
  delay(200);
  move(6, 80);
  delay(200);
  turnTo(90, 80); // turn to face platform
  delay(200);
  turnTo(90, 80);
  delay(200);
  move(10, 60); // go into platform
  delay(200);
  moveLift(-127); // lower lift
  delay(300);
  moveLift(0); // stop lift
  delay(200);
  unhookFrontClaw(); // unhook mobile goal on platform
  delay(400);
  frontLift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  // stack mobile goal

  move(-13, 80); // reverse from platform
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
  turnTo(0, 80); // turn to reverse
  delay(200);
  turnTo(0, 80); // correct turn
  delay(200);
  move(-20, 80); // reverse to right position for platform
  frontLift.move_absolute(1450, 127); // lift the lift
  delay(200);
  turnTo(90, 40); // turn to face platform at slow speed for accuracy
  delay(200);
  move(26, 80); // move into platform
  delay(200);
  moveLift(-127); // lower lift into platform
  delay(300);
  moveLift(0); // stop lift
  unhookFrontClaw(); // unhook alliance goal
  delay(400);
  // stack alliance goal

  frontLift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  move(-7, 80); // reverse from platform
  frontLift.move_absolute(-5, 127); // lower lift to ground
  move(-15, 80); // reverse from platform
  delay(200);
  turnTo(120, 60); // turn to center goal at slow speed for accuracy
  delay(200);
  move(-20, 80); // reverse to center goal
  delay(200);
  hookBackClaw(); // hook onto center goal
  delay(200);

  move(-44, 80); // move center to alliance zone
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
  move(-45, 80); // reverse against alliance goal
  delay(200);
  hookBackClaw(); // hook onto alliance goal

  delay(200);
  move(15, 200); // move away from wall
  delay(200);
  turnTo(90, 40); // turn to mobile goal
  delay(400);
  turnTo(90, 40);
  move(40, 80);
  hookFrontClaw(); // hook onto mobile goal
  delay(200);
  frontLift.move_absolute(1300, 127); // lift the lift
  turnTo(45, 80); // turn to desired stacking position
  delay(200);
  move(30, 80); // move to platform
  delay(200);
  turnTo(0, 80); // turn to platform
  delay(200);
  move(15, 80); // move to desired position
  delay(200);
  turnTo(90, 80); // turn to platform
  delay(200);
  move(30, 80); // move into platform
  delay(200);
  moveLift(-127); // lower lift
  delay(300);
  moveLift(0); // stop lift
  unhookFrontClaw(); // stack mobile goal

  delay(400);
  frontLift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  move(-7, 80); // reverse from platform
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
  move(16, 80);
  hookFrontClaw(); // hook onto alliance goal
  delay(200);
  move(-10, 80);
  frontLift.move_absolute(1300, 127); // lift the lift
  turnTo(90,40);
  delay(400);
  turnTo(90,40);
  move(22, 80); // move into platform
  delay(200);
  moveLift(-127); // lower lift
  delay(300);
  moveLift(0); // stop lift
  delay(200);
  move(5, 80); // move more into platform to stack in correct position
  delay(200);
  unhookFrontClaw(); // stack alliance goal

  delay(400);
  move(-20, 80); // reverse from platform
  frontLift.move_absolute(-5, 127); // lower lift to ground


}
