#include "vex.h"
#define pulse 100         
#define RobotLife 150 
#define MaxTorque 0.45 
    double four;
    double one;
    double two;
   
  
    double speedFL;
    double speedFR;
    double speedRR;
    double speedRL;
    int armSpeedPCT = 80;
    int Rzero = 0;
int Stop;
int StackerState =0;
    
    
    void ZeroStacker (){
          Stacker.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
            while ((Stacker.vex::motor::torque(torqueUnits::Nm))<=(MaxTorque)){ 
              
              //wait for torque value to reach max torque
              vex::task::sleep(10);
            }
             Stacker.resetRotation();
             Stacker.stop(vex::brakeType::brake);
             StackerState=0;     
        }

void FlipOut(){
    
     Arm.spin(vex::directionType::rev,127, vex::velocityUnits::pct);
     task::sleep(700);
     Arm.stop(vex::brakeType::coast);

     task::sleep(100);
      Roller1.stop(vex::brakeType::hold);
      Roller2.stop(vex::brakeType::hold);
     
     Arm.spin(vex::directionType::fwd,127, vex::velocityUnits::pct);

     task::sleep(800);
     Arm.stop(vex::brakeType::coast);
}
int logo(){
    
    int color1 = 0;
    int a;
    int b;
    int c;
    int d;
    
    while(true){
        //Reset values a, b, c, and d
     
        a = b = c = d = 0;
        //Create Random Colors Every Loop
         color1++;
        if(color1 >= 7) color1 = 0;
        if(color1 == 0)Brain.Screen.setPenColor(color::red);   
        else if(color1 == 1) Brain.Screen.setPenColor(color::green); 
        else if(color1 == 2) Brain.Screen.setPenColor(color::blue);     
        else if(color1 == 3) Brain.Screen.setPenColor(color::yellow);  
        else if(color1 == 4) Brain.Screen.setPenColor(color::purple); 
        else if(color1 == 5) Brain.Screen.setPenColor(color::orange);  
        else if(color1 == 6) Brain.Screen.setPenColor(color::cyan); 
     
        //Draw Rainbow Circle
  //Brain.Screen.setPenWidth( 3 );  
    //Brain.Screen.drawRectangle( 80, 12, 320, 180);
       
     
        //Draw Rainbow Line
        for(int j = 1; j <= 6; j ++){
          
    Brain.Screen.setPenWidth( 5 );  

    Brain.Screen.setFont( mono60); 
    Brain.Screen.setPenWidth( 5 );
    Brain.Screen.printAt( 207, 92, "BURNSVIEW" );
    Brain.Screen.setPenWidth( 7 );
    Brain.Screen.printAt( 222, 170, "ROBOTICS" );
    //Brain.Screen.drawImageFromFile( "SAHIL.PNG", 20, 45 );
 
   
            a -= 2;
            b++;
        }
     
        Brain.Screen.setPenColor(color::white); 
     
       
        task::sleep(1000); 
     
    }     
} 

void Rotate(){
        
        FL.resetRotation();
         RL.resetRotation();
          RR.resetRotation();
           FR.resetRotation();

        
        RL.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        FL.spin(vex::directionType::rev,100,vex::velocityUnits::pct);




if ((RL.rotation(rotationUnits::deg)) >=10){
   RR.stop(vex::brakeType::hold);
        FR.stop(vex::brakeType::hold);
         RL.stop(vex::brakeType::hold);
        FL.stop(vex::brakeType::hold);
}
}
void DriveBS(){
        RL.spin(vex::directionType::rev,40,vex::velocityUnits::pct);
        RR.spin(vex::directionType::rev,40,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,40,vex::velocityUnits::pct);
        FL.spin(vex::directionType::rev,40,vex::velocityUnits::pct);
}
void DriveFS(){
        RL.spin(vex::directionType::fwd,35,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,35,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,35,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,35,vex::velocityUnits::pct);
}
void DriveF(){
        RL.spin(vex::directionType::fwd,35,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,35,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,35,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,35,vex::velocityUnits::pct);
}
void DriveFast(){
        RL.spin(vex::directionType::fwd,65,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,65,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,65,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,65,vex::velocityUnits::pct);
}
void DriveB(){
        RL.spin(vex::directionType::rev,55,vex::velocityUnits::pct);
        RR.spin(vex::directionType::rev,55,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,55,vex::velocityUnits::pct);
        FL.spin(vex::directionType::rev,55,vex::velocityUnits::pct);
}
void TurnRight(){
        RL.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
        RR.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
}
void TurnLeft(){
        RL.spin(vex::directionType::rev,156,vex::velocityUnits::rpm);
        RR.spin(vex::directionType::fwd,156,vex::velocityUnits::rpm);
        FR.spin(vex::directionType::fwd,156,vex::velocityUnits::rpm);
        FL.spin(vex::directionType::rev,156,vex::velocityUnits::rpm);
}
void StrafeR(){
        RL.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
}

void StrafeL(){
        RL.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        RR.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        FL.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
}
void DriveStop(){
        RL.stop(vex::brakeType::coast);
        RR.stop(vex::brakeType::coast);
        FR.stop(vex::brakeType::coast);
        FL.stop(vex::brakeType::coast);
}
void DriveStopH(){
        RL.stop(vex::brakeType::hold);
        RR.stop(vex::brakeType::hold);
        FR.stop(vex::brakeType::hold);
        FL.stop(vex::brakeType::hold);
}
void RollerIntake(){
        Roller1.spin(vex::directionType::rev,100 , vex::velocityUnits::pct);
        Roller2.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
}
void RollerIntakeF(){
        Roller1.spin(vex::directionType::rev,115 , vex::velocityUnits::pct);
        Roller2.spin(vex::directionType::fwd,115, vex::velocityUnits::pct);
}
void RollerIntakeS(){
        Roller1.spin(vex::directionType::rev,50 , vex::velocityUnits::pct);
        Roller2.spin(vex::directionType::fwd,50, vex::velocityUnits::pct);
}
void RollerOutake(){
        Roller1.spin(vex::directionType::fwd, 21 , vex::velocityUnits::pct);
        Roller2.spin(vex::directionType::rev, 21, vex::velocityUnits::pct);
}
void RollerOutakeS(){
        Roller1.spin(vex::directionType::fwd, 15 , vex::velocityUnits::pct);
        Roller2.spin(vex::directionType::rev, 15, vex::velocityUnits::pct);
}
void RollerStop(){
        Roller1.stop(vex::brakeType::hold);
        Roller2.stop(vex::brakeType::hold);       
}

void PlaceStack(){
   Stacker.rotateFor(1650,rotationUnits::deg,80, vex::velocityUnits::pct);
}

void ArmUp(){
   Arm.spin(vex::directionType::rev,127, vex::velocityUnits::pct);
}

void ArmDown(){
  Arm.spin(vex::directionType::fwd,30, vex::velocityUnits::pct);
}

void SonarMoveF(int Dist){
        RL.spin(vex::directionType::fwd,70,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,70,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,70,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,70,vex::velocityUnits::pct);
   while(Sonar1 && Sonar2<= Dist ){
  
        
        task::sleep(10);
   }
       
        RL.stop(vex::brakeType::coast);
        RR.stop(vex::brakeType::coast);
        FR.stop(vex::brakeType::coast);
        FL.stop(vex::brakeType::coast);
        
  }

  void SonarMoveFS(int Dist){
        RL.spin(vex::directionType::fwd,45,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,45,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,45,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,45,vex::velocityUnits::pct);
   while(Sonar1 && Sonar2<= Dist ){
  
        
        task::sleep(10);
   }
       
        RL.stop(vex::brakeType::coast);
        RR.stop(vex::brakeType::coast);
        FR.stop(vex::brakeType::coast);
        FL.stop(vex::brakeType::coast);
        
  }

void SonarMoveB(int Dist){
        RL.spin(vex::directionType::rev,50,vex::velocityUnits::pct);
        RR.spin(vex::directionType::rev,50,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,50,vex::velocityUnits::pct);
        FL.spin(vex::directionType::rev,50,vex::velocityUnits::pct);
   while(Sonar1 && Sonar2>= Dist ){
  
        
        task::sleep(10);
   }
       
        RL.stop(vex::brakeType::coast);
        RR.stop(vex::brakeType::coast);
        FR.stop(vex::brakeType::coast);
        FL.stop(vex::brakeType::coast);
        
  }
void SonarTurnR(){
         
        RR.spin(vex::directionType::rev,40,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,40,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,40,vex::velocityUnits::pct);
        RL.spin(vex::directionType::fwd,40,vex::velocityUnits::pct);
     
   while(Sonar1 >= Sonar2){
  
        
        task::sleep(10);
   }
       
      
        RR.stop(vex::brakeType::hold);
        FR.stop(vex::brakeType::hold);
        RL.stop(vex::brakeType::hold);
        FL.stop(vex::brakeType::hold);
     
        
  }
void SonarTurnL(){
       
        FL.spin(vex::directionType::rev,40,vex::velocityUnits::pct);
        RL.spin(vex::directionType::rev,40,vex::velocityUnits::pct);
     
   while(Sonar1 >= Sonar2){
  
        
        task::sleep(10);
   }
       
      
        RR.stop(vex::brakeType::hold);
        FR.stop(vex::brakeType::hold);
        RL.stop(vex::brakeType::hold);
        FL.stop(vex::brakeType::hold);
     
        
  }
vex::competition Competition;

void pre_auton( void ) {
}

void autonomous( void ) {
  //Rotate();
  FlipOut(); //Robot follows the FlipOut Procedure
   Arm.spin(vex::directionType::fwd,7,vex::velocityUnits::pct);
task::sleep(400);
    //ZeroStacker(); // Zeroes the rotation of the Stacker Motor
   
   // Drives Forward to pick up the cubes
   DriveFS(); 
    RollerIntakeF();
    task::sleep(260);
    DriveStop();
    SonarMoveF(900);
    task::sleep(400);
    DriveB();
    task::sleep(730);
    DriveStopH();
    //SonarMoveB(850);
    
    TurnRight();
    task::sleep(350);
    DriveStop();

    DriveB();
    task::sleep(1190);
    DriveStop();

   
    TurnLeft();
  task::sleep(350);
  DriveStop();


  DriveFS(); 
    RollerIntakeF();
    task::sleep(260);
    DriveStop();
    SonarMoveFS(560);
    //SonarTurnL();
task::sleep(200);
    SonarMoveB(400);


    TurnRight();
    task::sleep(540);
    DriveStop();


   DriveF();
   task::sleep(1200);
   RollerOutake();
   task::sleep(3);
   DriveStop();

  
    StrafeR();
    Stacker.spin(vex::directionType::fwd,70,vex::velocityUnits::pct);
    task::sleep(700);
    DriveStop();
    
       RollerStop();
     DriveF();
     task::sleep(1100);
  
   
     DriveStop();
     Stacker.stop(vex::brakeType::coast);
     RollerStop();
     Stacker.resetRotation();
     Arm.spin(vex::directionType::fwd,8,vex::velocityUnits::pct);
      Stacker.rotateFor(1350,rotationUnits::deg,70, vex::velocityUnits::pct);
     RollerIntake();
     task::sleep(100);
       RollerStop();
       task::sleep(200);
     
       DriveBS(); 
       task::sleep(200);
        Stacker.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
      
     
       }



void usercontrol( void ) {
//Controller1.Screen.clearScreen();

  while (1) {
// Sonar Right is one
//Brain.Screen.printAt(300, 30, "distance: %f mm", Sonar1.distance(distanceUnits::mm));
//Brain.Screen.printAt(300, 50, "distance: %f mm", Sonar2.distance(distanceUnits::mm));
//Controller1.Screen.print( "rotation: %f degrees", Potent.value(rotationUnits::deg));


    //Controller1.Screen.clearScreen();
      //    Controller1.Screen.setCursor(1,1);
        //  Controller1.Screen.print("rotation: %f degrees", Gyro1.value(rotationUnits::deg));

       
         if (Controller1.ButtonR2.pressing()){
            Stacker.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
        }
        
        if (!Controller1.ButtonR1.pressing() && !Controller1.ButtonR2.pressing()  )
        {
            Stacker.stop(vex::brakeType::brake);
           
        }

        if ( !Controller1.ButtonR2.pressing()  )
        {
            Stacker.stop(vex::brakeType::brake);
           
        }
        
        if (Controller1.ButtonDown.pressing()){
          ZeroStacker(); 
        }
        
        if (Controller1.ButtonR1.pressing()){

Stacker.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
Arm.spin(vex::directionType::fwd,2, vex::velocityUnits::pct);  

if ((Stacker.rotation(rotationUnits::deg))>=1150){
 Stacker.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);
 Arm.spin(vex::directionType::fwd,2, vex::velocityUnits::pct);
}


if ((Stacker.rotation(rotationUnits::deg))>=2750){
  Stacker.stop(vex::brakeType::hold);
  Arm.stop(vex::brakeType::hold);
}


task::sleep(10);
        }
       
        
    
        
        
        // Arm's Code
        if (Controller1.ButtonL2.pressing()){
            Arm.spin(vex::directionType::fwd,90, vex::velocityUnits::pct);
    }
         if (Controller1.ButtonL1.pressing()){
            Arm.spin(vex::directionType::rev,127, vex::velocityUnits::pct);
            
        }
        
        if (!Controller1.ButtonL1.pressing() && !Controller1.ButtonL2.pressing()  )
        {
            Arm.stop(vex::brakeType::hold);
        }
        
        
        
        // Roller's Code
        if(Controller1.ButtonRight.pressing()) 
        {
            Roller1.spin(vex::directionType::rev,12.0 , vex::voltageUnits::volt);
            Roller2.spin(vex::directionType::fwd,12.0, vex::voltageUnits::volt);
        }
        if(Controller1.ButtonY.pressing()) 
        {
           Roller1.spin(vex::directionType::fwd, 8.0, vex::voltageUnits::volt);
            Roller2.spin(vex::directionType::rev, 8.0, vex::voltageUnits::volt);
        }
        if (!Controller1.ButtonRight.pressing() && !Controller1.ButtonY.pressing()  )
        { 
            Roller1.stop(vex::brakeType::hold);
            Roller2.stop(vex::brakeType::hold);
        }

         two= Controller1.Axis2.value();//movement
         one = Controller1.Axis1.value(); //rotation
         four=Controller1.Axis4.value();
      
        
           
       
            speedFL=   two + one;
            speedFR =  two -one;
            speedRR =  two -one;
            speedRL =  two +one;
        RL.spin(vex::directionType::fwd,speedRL/1.2,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,speedRR/1.2,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,speedFR/1.2,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,speedFL/1.2,vex::velocityUnits::pct);
if (four){
        RL.spin(vex::directionType::rev,four,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,four,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,four,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,four,vex::velocityUnits::pct);
}


      
        
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
 
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  //vex::task rainbow(logo);
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}