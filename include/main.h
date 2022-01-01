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

extern Motor fr;
extern Motor br;
extern Motor br2;
extern Motor fl;
extern Motor bl;
extern Motor bl2;

extern Motor frontLift;

extern ADIDigitalOut frontClaw;
extern ADIDigitalOut backClaw;

extern Motor ringIntake;

extern Controller master;

extern Imu inertial;

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
