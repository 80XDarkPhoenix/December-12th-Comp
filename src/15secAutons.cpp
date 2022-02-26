#include "main.h"
#include "math.h"

using namespace pros;

// mobile goal

void rightMobileFast() {
	frontLift.move_absolute(-5, 50);
	move(48, 127, true);
	delay(200);
	move(-200, 127);
}

void leftMobileFast() {
	frontLift.move_absolute(-5, 50);
	move(53, 127, true);
	delay(200);
	move(-200, 127);
}

void rightMobileAlliance() {
	move(48, 127, true); // move to mobile goal
	delay(200);
	move(-25, 127);

	delay(400);
	turnTo(-90, 80);
	unhookBackClaw();
	move(-14, 80);
	hookBackClaw();
	delay(200);
	moveRingIntake(127);
	delay(4000);
	move(20, 80);
	unhookBackClaw();
}

void leftMobileAlliance() {
	move(53, 127, true); // move to mobile goal
	delay(400);
	move(-54, 127);
	delay(400);
	turnTo(110, 80);
	delay(400);
	move(-16, 80);
	hookBackClaw();
	frontLift.move_absolute(500, 100);
	delay(400);
	moveRingIntake(127);
	move(36, 30);
	unhookBackClaw();
}

void winPoint() {
	move(-2.5, 80);
	hookBackClaw();
	delay(200);
	moveRingIntake(127);
	delay(3000);
	moveRingIntake(0);
	unhookBackClaw();
	move(10, 80);
	delay(400);
	turnTo(90, 80);
	delay(400);
	move(24, 80);
	delay(400);
	turnTo(0, 80);
	delay(400);
	move(-115, 80);
	delay(400);
	turnTo(0, 80);
	delay(400);
	hookBackClaw();
	delay(400);
	moveRingIntake(127);
	frontLift.move_absolute(600, 120);
	move(15, 80);
	delay(400);
	turnTo(-90, 80);
	delay(200);
	move(36, 30);
}

void rightCenter() {

}
