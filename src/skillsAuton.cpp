#include "main.h"
#include "math.h"

using namespace pros;

void skills() {
  unhookBackClaw();
  unhookFrontClaw();

  move(-7, 80);
  hookBackClaw();
  delay(200);
  // hooked red alliance goal with back claw

  move(12, 80);
  moveRingIntake(127);
  delay(200);
  turnTo(45, 80);
  delay(200);
  move(12, 80);
  delay(200);
  turnTo(90, 80);
  delay(200);
  move(24, 80);
  delay(200);
  turnTo(127, 80);
  delay(200);
  move(24, 80, true);
  // hooked onto mobile goal

  delay(200);
  moveLift(127);
  delay(1500);
  moveLift(0);
  move(63, 60);
  delay(600);
  turnTo(90, 80);
  delay(200);
  move(5, 80);
  moveLift(-127);
  delay(300);
  moveLift(0);
  unhookFrontClaw();
  frontLift.move_absolute(1450, 127);
  delay(200);
  // stack mobile goal

  move(-10, 80);
  frontLift.move_absolute(-5, 127);
  delay(100);
  turnTo(90, 80);
  delay(100);
  unhookBackClaw();
  delay(200);
  move(-10, 80);
  delay(200);
  move(7, 80);
  delay(200);
  turnTo(-90, 80);
  delay(200);
  move(11, 80, true); // hook onto alliance goal
  delay(200);
  turnTo(0, 40);
  delay(200);
  move(-13, 80);
  frontLift.move_absolute(1450, 127);
  delay(200);
  turnTo(90, 40);
  delay(200);
  move(20, 80);
  moveLift(-127);
  delay(300);
  moveLift(0);
  unhookFrontClaw();
  // stack alliance goal

  frontLift.move_absolute(1450, 127);
  delay(200);
  move(-5, 80);
  frontLift.move_absolute(-5, 127);
  move(-15, 80);
  delay(200);
  turnTo(100, 60);
  delay(200);
  move(-20, 80);
  delay(200);
  hookBackClaw(); // hook onto center goal
  delay(200);

  move(-30, 80); // move center to alliance zone
  delay(200);
  turnTo(180, 80);
  delay(200);
  unhookBackClaw(); // let go of center goal
  move(33, 80);
  delay(400);
  turnTo(0, 40);
  delay(400);
  turnTo(0, 40);
  delay(400);
  move(-20, 80);
  delay(200);
  hookBackClaw(); // hook onto alliance goal

  delay(200);
  move(15, 200);
  delay(200);
  turnTo(90, 80);
  delay(200);
  move(40, 80, true); // hook onto mobile goal
  delay(200);
  frontLift.move_absolute(1450, 127);
  turnTo(45, 80);
  delay(200);
  move(40, 80); // move to platform
  delay(200);
  turnTo(0, 80);
  delay(200);
  move(10, 80);
  delay(200);
  turnTo(90, 80);
  delay(200);
  move(12, 80);
  delay(200);
  moveLift(-127);
  delay(300);
  moveLift(0);
  unhookFrontClaw(); // stack mobile goal

  delay(200);
  frontLift.move_absolute(1450, 127);
  delay(200);
  move(-5, 80);
  frontLift.move_absolute(-5, 127);
  delay(200);
  move(-5, 80);
  delay(200);
  turnTo(90, 80);
  delay(200);
  move(-10, 80);
  unhookBackClaw();
  delay(200);
  move(7, 80);
  delay(200);
  turnTo(-90, 80);
  delay(200);
  turnTo(-90, 80);
  delay(200);
  move(12, 80, true); // hook onto alliance goal
  delay(200);
  frontLift.move_absolute(1450, 127);
  turnTo(90, 80);
  delay(200);
  move(20, 80);
  delay(200);

  move(12, 80);
  delay(200);
  moveLift(-127);
  delay(300);
  moveLift(0);
  delay(200);
  move(5, 80);
  delay(200);
  unhookFrontClaw(); // stack alliance goal

  delay(200);
  move(-8, 80);
  frontLift.move_absolute(-5, 127);
  delay(200);
  turnTo(180, 80);
  delay(200);
  turnTo(180, 80);
  delay(200);
  move(-65, 80);
  delay(200);
  hookBackClaw();
  delay(400);
  move(120, 80);



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
