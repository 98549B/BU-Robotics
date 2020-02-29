/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"
using namespace vex;
vex::brain Brain;
vex::motor Roller1 (vex::PORT11, vex::gearSetting::ratio18_1,false);
vex::motor Roller2 (vex::PORT6, vex::gearSetting::ratio18_1,false);
vex::motor Stacker (vex::PORT7, vex::gearSetting::ratio18_1,true);
vex::motor Arm (vex::PORT2, vex::gearSetting::ratio18_1,false);
vex::motor RL (vex::PORT10, vex::gearSetting::ratio18_1,false);
vex::motor FL (vex::PORT19, vex::gearSetting::ratio18_1,false);
vex::motor FR (vex::PORT5, vex::gearSetting::ratio18_1,true);
vex::motor RR (vex::PORT1, vex::gearSetting::ratio18_1,true);
vex::controller Controller1;