#include "main.h"

#include "math.h"

using namespace pros;

void skillsAuton() {
  // start 90 degrees left

  // make sure claws start up
  unhookFrontClaw();
  unhookBackClaw();

  move(-, 110); // move back to alliance goal
  delay(50);
  frontDistanceMove();
  hookBackClaw();
  delay(500);
  moveRingIntake(100);

  move(, 110);
  delay(50);
  frontDistanceMove();
  turn(90, 110);
  moveRingIntake(0);
  backDistanceMove();
  delay(50);
  move(, 110);
  delay(50);
  frontDistanceMove();
  delay(50);
  turn(45, 110);

  move(, 110);
  hookFrontClaw();
  delay(500);
  moveLift(110);
  move(, 110);
  delay(50);
  turn(45, 110);
  move(, 110);
  delay(50);
  turn(-90, 110);
  delay(50);
  move(, 110);
  unhookFrontClaw();
  delay(500);

  move(-, 110);
  lowerFrontLift();
  turn(-90, 110);
  unhookBackClaw();
  delay(50);

  move(, 110);
  hookFrontClaw();
  delay(500);

  move(-, 110);
  delay(50);
  turn(45, 110);
  delay(50);
  move(-, 110);
  hookBackClaw();
  delay(500);
  move(-, 110);
  unhookBackClaw();
  delay(50);

  move(, 110);
  delay(50);
  move(-, 110);
  hookBackClaw();
  delay(500);

  moveLift(110);
  move(, 110);
  delay(50);
  turn(90, 110);
  move(, 110);
  unhookFrontClaw();
  delay(500);
  moveLift(0);

  move(-, 110);
  delay(50);
  turn(90, 110);
  moveLift(-110)
  frontDistanceMove();
  delay(50);
  move(-, 110);
  moveLift(0);
  delay(50);
  turn(-90, 110);
  delay(50);

  move(, 110);
  hookFrontClaw();
  delay(500);
  moveLift(110);
  move(, 110);
  delay(50);
  turn(-45, 110);
  delay(50, 110);
  move(, 110);
  unhookFrontClaw();
  delay(500);

  move(-, 110);
  lowerFrontLift();
  turn(45, 110);
  move(, 110);
  hookFrontClaw();
  delay(500);
  move(-, 110);
  delay(50);
  turn(-180, 110);
  unhookBackClaw();
  delay(50);

  move(, 110);
  delay(50);
  turn(45, 110);
  moveLift(110);
  delay(50);
  move(, 110);
  unhookBackClaw();
  delay(500);
  move(-, 127);
  moveLift(-127);
}
