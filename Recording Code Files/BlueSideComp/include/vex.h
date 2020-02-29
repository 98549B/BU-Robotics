#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"
using namespace vex;

vex::brain Brain;
vex::sonar Sonar1( Brain.ThreeWirePort.A);
vex::sonar Sonar2( Brain.ThreeWirePort.C);
vex::gyro Gyro1( Brain.ThreeWirePort.F);
vex::motor Roller1 (vex::PORT12, vex::gearSetting::ratio18_1,false);
vex::motor Roller2 (vex::PORT20, vex::gearSetting::ratio18_1,false);
vex::motor Stacker (vex::PORT5, vex::gearSetting::ratio36_1,false);
vex::motor Arm (vex::PORT14, vex::gearSetting::ratio18_1,false);
vex::motor RL (vex::PORT10, vex::gearSetting::ratio18_1,false);
vex::motor FL (vex::PORT7, vex::gearSetting::ratio18_1,false);
vex::motor FR (vex::PORT11, vex::gearSetting::ratio18_1,true);
vex::motor RR (vex::PORT4, vex::gearSetting::ratio18_1,true);
vex::controller Controller1;

