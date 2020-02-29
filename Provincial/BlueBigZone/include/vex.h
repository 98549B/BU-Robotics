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
vex::pot Potent( Brain.ThreeWirePort.F);
vex::inertial Inert1 = inertial(PORT16);
vex::motor Roller1 (vex::PORT6, vex::gearSetting::ratio18_1,false);
vex::motor Roller2 (vex::PORT20, vex::gearSetting::ratio18_1,false);
vex::motor Stacker (vex::PORT10, vex::gearSetting::ratio18_1,false);
vex::motor Arm (vex::PORT1, vex::gearSetting::ratio18_1,false);
vex::motor RL (vex::PORT11, vex::gearSetting::ratio18_1,false);
vex::motor FL (vex::PORT19, vex::gearSetting::ratio18_1,false);
vex::motor FR (vex::PORT18, vex::gearSetting::ratio18_1,true);
vex::motor RR (vex::PORT7, vex::gearSetting::ratio18_1,true);
vex::controller Controller1;


