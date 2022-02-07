#include "main.h"
#include "math.h"

using namespace pros;

void skillsAuton() {
  // start 90 degrees left

  // make sure claws start up
  unhookFrontClaw();
  unhookBackClaw();

  // hook on to alliance goal
  moveLift(127);
  move(-22, 110); // move back to alliance goal
  moveLift(0);
  hookBackClaw();
  delay(500);
  moveRingIntake(100);

  // in between alliance goal and mobile goal
  move(12, 110);
  delay(50);
  turn(45, 110);
  moveRingIntake(0);
  delay(50);
  move(10, 110);
  delay(50);
  turn(58, 110);
  delay(50);
  moveLift(-127);
  move(34, 110);
  moveLift(0);
  delay(50);
  turn(45, 110);
  delay(50);

  // claw on mobile goal
  move(14, 110);
  hookFrontClaw();
  delay(500);

  moveLift(127);
  moveRingIntake(100);
  move(65, 110);
  moveLift(0);
  moveRingIntake(0);
  delay(50);
  turn(-45, 100);
  delay(50);
  move(10, 120);
  moveLift(-127);
  delay(200);
  moveLift(0);
  unhookFrontClaw();
  move(-9, 120);
  delay(50);
  turn(-95, 110);
  delay(50);
  unhookBackClaw();
  delay(200);
  moveLift(-127);
  move(52, 120);
  moveLift(0);
  hookFrontClaw();
  delay(250);
  move(-20, 110);
  turn(62,100);
  delay(50);
  move(-100, 120);
}
