#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#include "api.h"

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
