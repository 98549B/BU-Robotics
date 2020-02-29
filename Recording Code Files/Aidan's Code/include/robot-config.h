#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "v5.h"
#include "v5_vcs.h"
using namespace vex;

//Motor, Controller and Brain Configs
vex::brain Brain;
vex::motor Roller1 (vex::PORT3, vex::gearSetting::ratio18_1,false);
vex::motor Roller2 (vex::PORT4, vex::gearSetting::ratio18_1,false);
vex::motor Stacker (vex::PORT5, vex::gearSetting::ratio18_1,false);
vex::motor Arm (vex::PORT6, vex::gearSetting::ratio18_1,false);
vex::motor RL (vex::PORT11, vex::gearSetting::ratio18_1,true);
vex::motor FL (vex::PORT12, vex::gearSetting::ratio18_1,false);
vex::motor FR (vex::PORT16, vex::gearSetting::ratio18_1,false);
vex::motor RR (vex::PORT19, vex::gearSetting::ratio18_1,true);
vex::controller Controller1;