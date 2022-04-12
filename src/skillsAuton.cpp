#include "main.h"
#include "math.h"

void skillsAuton() {
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
