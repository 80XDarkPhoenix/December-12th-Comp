#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#include "api.h"
#include "15secAutons.hpp"
#include "autonFunctions.hpp"
#include "opcontrolFunctions.hpp"
#include "skillsAuton.hpp"

using namespace pros;

// base
extern Motor r1;
extern Motor r2;
extern Motor r3;
extern Motor l1;
extern Motor l2;
extern Motor l3;

// lift
extern Motor frontLift;

// claws
extern ADIDigitalOut frontClaw;
extern ADIDigitalOut backClaw;

// ring intake
extern Motor ringIntake;

// controller
extern Controller master;

// sensors

// inertial sensor
extern Imu inertial;

extern ADIEncoder rEncoder;
extern ADIEncoder lEncoder;

// distance sensors
//extern Distance frontDistance;
//extern Distance backDistance;

#ifdef __cplusplus
extern "C" {
#endif

  void autonomous();
  void initialize();
  void disabled();
  void competition_initialize();
  void opcontrol();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#endif
#endif
