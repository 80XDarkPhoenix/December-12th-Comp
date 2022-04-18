#include "main.h"
#include "math.h"

void skills() {
  // make sure claws are up
  unhookTilter();
  unhookClaw();

  move(-7, 80); // reverse to alliance goal
  hookTilter(); // hook onto alliance goal
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
  unhookClaw(); // unhook mobile goal on platform
  delay(400);
  lift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  // stack mobile goal

  move(-13, 80); // reverse from platform
  lift.move_absolute(-5, 127); // lower lift to ground
  delay(100);
  turnTo(90, 80); // correct turn
  delay(100);
  unhookTilter(); // let go of alliance goal
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
  lift.move_absolute(1450, 127); // lift the lift
  delay(200);
  turnTo(90, 40); // turn to face platform at slow speed for accuracy
  delay(200);
  move(26, 80); // move into platform
  delay(200);
  moveLift(-127); // lower lift into platform
  delay(300);
  moveLift(0); // stop lift
  unhookClaw(); // unhook alliance goal
  delay(400);
  // stack alliance goal

  lift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  move(-7, 80); // reverse from platform
  lift.move_absolute(-5, 127); // lower lift to ground
  move(-15, 80); // reverse from platform
  delay(200);
  turnTo(120, 60); // turn to center goal at slow speed for accuracy
  delay(200);
  move(-20, 80); // reverse to center goal
  delay(200);
  hookTilter(); // hook onto center goal
  delay(200);

  move(-44, 80); // move center to alliance zone
  delay(200);
  turnTo(180, 80); // turn to alliance goal
  delay(200);
  unhookTilter(); // let go of center goal
  move(33, 80); // move to alliance goal
  delay(400);
  turnTo(0, 40); // turn with back facing alliance goal
  delay(400);
  turnTo(0, 40); // correct turn
  delay(400);
  move(-45, 80); // reverse against alliance goal
  delay(200);
  hookTilter(); // hook onto alliance goal

  delay(200);
  move(15, 200); // move away from wall
  delay(200);
  turnTo(90, 40); // turn to mobile goal
  delay(400);
  turnTo(90, 40);
  move(40, 80);
  hookClaw(); // hook onto mobile goal
  delay(200);
  lift.move_absolute(1300, 127); // lift the lift
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
  unhookClaw(); // stack mobile goal

  delay(400);
  lift.move_absolute(1450, 127); // lift the lift to leave platform
  delay(200);
  move(-7, 80); // reverse from platform
  lift.move_absolute(-5, 127); // lower lift to the grounf
  delay(200);
  move(-5, 80); // reverse from platform
  delay(200);
  turnTo(90, 80); // correct turn
  delay(200);
  move(-10, 80); // reverse from platform
  unhookTilter(); // unhook alliance goal
  delay(200);
  move(7, 80); // move away from alliance goal
  delay(200);
  turnTo(-90, 80); // turn to alliance goal
  delay(200);
  turnTo(-90, 80); // correct turn
  delay(200);
  move(16, 80);
  hookClaw(); // hook onto alliance goal
  delay(200);
  move(-10, 80);
  lift.move_absolute(1300, 127); // lift the lift
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
  unhookClaw(); // stack alliance goal

  delay(400);
  move(-20, 80); // reverse from platform
  lift.move_absolute(-5, 127); // lower lift to ground
}

void newPathSkills() {
  unhookClaw();
  unhookTilter();

  move(-0, 100);// reverse to alliance goal (small amount)
  hookTilter(); // and back claw on goal
  delay(0);
  move(0, 100); //move a little (around same amount that robot reversed at beginning)
  turnTo(90, 100);
  move(0, 100); // move around 2 field tiles
  hookClaw(); // and front claw on goal
  delay(0);
  turnTo(135, 100);
  moveLift(100); // lift up
  move(0, 100); // move to platform
  moveLift(-100); // lower lift a little
  delay(0);
  unhookClaw(); // let go of goal
  delay(0);
  // lift lift a little
  // reverse from platform
  turnTo(0, 100);
  delay(0);
  unhookTilter(); // back unclaw
  delay(0);
  move(0, 100); // move to alliance goal
  hookClaw(); // front hook
  move(-0, 100); // reverse
  turnTo(45, 100);
  move(-0, 100); // reverse to center
  hookTilter(); // back claw
  move(-0, 100);; // reverse more
  unhookTilter(); // unhook back claw
  moveLift(100); // lift lift
  move(0, 100); // move a little
  turnTo(0, 100);
  move(-0, 100); // reverse a little
  hookTilter(); // hook back claw
  move(0, 100); // move
  turnTo(-90, 100);
  move(0, 100); // move into platform
  moveLift(-100); // lower lift a little
  unhookClaw(); // unhook front claw
  moveLift(100); // lift lift a little
  move(-0, 100); // reverse from platform
  turnTo(0, 100);
  move(-0, 100); // reverse
  turnTo(90, 100);
  move(0, 100); // move to alliance goal
  hookClaw(); // and hook on
  turnTo(45, 100);
  moveLift(100); // lift lift
  move(0, 100); // move towards platform
  moveLift(100); // lower lift a little
  unhookClaw(); // let go of goal
  moveLift(100); // lift lift a little
  move(-0, 100); // reverse from platform a little
  turnTo(0, 100);
  move(0, 100); // move to alliance goal from beginning
  hookClaw(); // and hook on
  moveLift(100); // lift lift
  turnTo(90, 100);
  move(0, 100); // move into platform
  moveLift(-100); // lower lift a little
  unhookClaw(); // let go of goal
  moveLift(100); // lift lift a little
  move(-0, 100); // reverse from platform
  turnTo(0, 100);
  move(-0, 100); // reverse to past alliance goal
  turnTo(45, 100);
  move(0, 100); // move to alliance goal
  hookClaw(); // and hook on
  // reverse a little
  turnTo(-45, 100);
  unhookTilter(); // let go of back goal
  move(0, 100); // move to platform
  moveLift(-100); // lower lift a little
  unhookClaw(); // unhook goal
  moveLift(100); // lift lift a little
  move(-0, 100); // reverse
}
