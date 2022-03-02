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
  delay(200);
  moveLift(127);
  delay(1500);
  moveLift(0);
  move(63, 80);
  delay(600);
  turnTo(90, 80);
  delay(200);
  move(7, 80);
  moveLift(-127);
  delay(300);
  moveLift(0);
  unhookFrontClaw();
  frontLift.move_absolute(1450, 127);
  delay(200);
  frontLift.move_absolute(-5, 127);
  delay(200);
  delay(100);
  move(-10, 80);
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
  move(9, 80, true);
  delay(200);
  turnTo(0, 90);
  delay(200);
  move(-13, 80);
  frontLift.move_absolute(1450, 127);
  delay(200);
  turn(90, 80);
  delay(200);
  move(20, 80);
  moveLift(-127);
  delay(300);
  moveLift(0);
  unhookFrontClaw();
//  move(, 80);

}
