#include "vex.h"
#define pulse 100         
#define RobotLife 150 
#define MaxTorque 0.5 
    double four;
    double one;
    double two;
    uint8_t DataOne[RobotLife];
    uint8_t DataTwo[RobotLife];
    uint8_t DataThree[RobotLife];
    uint8_t DataFour[RobotLife];
    bool Button [8];
    int robotCycle = 0;
    int isRecording = 0; //0 is not recording , 1 is recording
    double speedFL;
    double speedFR;
    double speedRR;
    double speedRL;
    int armSpeedPCT = 80;
    int Rzero = 0;
int Stop;
int StackerState =0;
    
    int screenrate=0;
    timer myTimer;   
    double wakeTime; //time to wake up
    double sleepTime; //time now
    double restTime;  //resting time waiting for stuff
    bool restFlag=1;

void FlushToSDcard (){ //Start of FlushToSDcard

    // write test data to SD Card
    int DataOneWritten = Brain.SDcard.savefile( "dataOne.Skills", DataOne, sizeof(DataOne) );
    int DataTwoWritten = Brain.SDcard.savefile( "dataTwo.Skills", DataTwo, sizeof(DataTwo) );
    int DataThreeWritten = Brain.SDcard.savefile( "dataThree.Skills", DataThree, sizeof(DataThree) );
    int DataFourWritten = Brain.SDcard.savefile( "dataFour.Skills", DataFour, sizeof(DataFour) );
    if( DataOneWritten > 0 ) {
        // display on screen how many bytes we wrote
        Brain.Screen.setCursor( 2, 2 );
        Brain.Screen.print( "We wrote %d bytes from DataOne to the SD Card", DataOneWritten );
    }
    
    else {
        Brain.Screen.printAt( 10, 40, "Error writing to the SD Card" );        
    }
     if( DataTwoWritten > 0 ) {
        // display on screen how many bytes we wrote
        Brain.Screen.setCursor( 4, 2 );
        Brain.Screen.print( "We wrote %d bytes from DataTwo to the SD Card", DataTwoWritten );
    }
    
    else {
        Brain.Screen.printAt( 20, 40, "Error writing DataTwo to the SD Card" );        
    } 

 if( DataThreeWritten > 0 ) {
        // display on screen how many bytes we wrote
        Brain.Screen.setCursor( 6, 2 );
        Brain.Screen.print( "We wrote %d bytes from DataThree to the SD Card", DataThreeWritten );
    }
    
    else {
        Brain.Screen.printAt( 30, 40, "Error writing DataThree to the SD Card" );        
    }
    if( DataFourWritten > 0 ) {
        // display on screen how many bytes we wrote
        Brain.Screen.setCursor( 6, 2 );
        Brain.Screen.print( "We wrote %d bytes from DataThree to the SD Card", DataFourWritten );
    }
    
    else {
        Brain.Screen.printAt( 30, 40, "Error writing DataThree to the SD Card" );        
    }

}// End of FlushToSDcard

void ReadFromSDcard(){ //Start of ReadFromSDcard
  // now read it back into a different buffer
        int ReadOne = Brain.SDcard.loadfile( "dataOne.Skills", DataOne, sizeof(DataOne) );
        int ReadTwo = Brain.SDcard.loadfile( "dataTwo.Skills", DataTwo, sizeof(DataTwo) );
        int ReadThree = Brain.SDcard.loadfile( "dataThree.Skills", DataThree, sizeof(DataThree));
        int ReadFour = Brain.SDcard.loadfile( "dataFour.Skills", DataFour, sizeof(DataFour));
        // display on screen how many bytes we read
        Brain.Screen.setCursor( 3, 2 );
        Brain.Screen.print( "We read %d bytes from the SD Card", (ReadOne+ReadTwo+ReadThree+ReadFour) );
  
  }//End of ReadFromSDcard
void ZeroStacker (){
          Stacker.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
            while ((Stacker.vex::motor::torque(torqueUnits::Nm))<=(MaxTorque)){ 
              
              //wait for torque value to reach max torque
              vex::task::sleep(10);
            }
             Stacker.resetRotation();
             Stacker.stop(vex::brakeType::brake);
             StackerState=0;
             
            Controller1.Screen.clearScreen();
            Controller1.Screen.setCursor( 1,1);
            Controller1.Screen.print("Zeroed");      
        }

void FlipOut(){
     Arm.spin(vex::directionType::rev,127, vex::velocityUnits::pct);
     task::sleep(300);
     Arm.stop(vex::brakeType::coast);
     
     Arm.spin(vex::directionType::fwd,127, vex::velocityUnits::pct);
     
     task::sleep(300);
     Arm.stop(vex::brakeType::coast);
}

void DriveF(){
        RL.spin(vex::directionType::fwd,60,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,60,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,60,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,60,vex::velocityUnits::pct);
}

void DriveB(){
        RL.spin(vex::directionType::rev,60,vex::velocityUnits::pct);
        RR.spin(vex::directionType::rev,60,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,60,vex::velocityUnits::pct);
        FL.spin(vex::directionType::rev,60,vex::velocityUnits::pct);
}
void TurnRight(){
        RL.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
        RR.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
}
void TurnLeft(){
        RL.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
        FL.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
}
void StrafeR(){
        RL.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
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
void RollerIntake(){
        Roller1.spin(vex::directionType::rev,90 , vex::velocityUnits::pct);
        Roller2.spin(vex::directionType::fwd,90, vex::velocityUnits::pct);
}
void RollerOutake(){
        Roller1.spin(vex::directionType::fwd, 50 , vex::velocityUnits::pct);
        Roller2.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
}
void RollerStop(){
        Roller1.stop(vex::brakeType::hold);
        Roller2.stop(vex::brakeType::hold);       
}

vex::competition Competition;

void pre_auton( void ) {

}

void autonomous( void ) {
  
    FlipOut();
    DriveF();
    RollerIntake();
    task::sleep(2200);
    DriveStop();
    RollerStop();
    StrafeR();
   task::sleep(200);
   DriveStop();
   task::sleep(200);
    DriveF();
    RollerIntake();
    task::sleep(2200);
    DriveStop();
    RollerStop();
    task::sleep(200);
    StrafeR();
    task::sleep(1000);
    DriveStop();


    
      
    
       Controller1.Screen.clearScreen();
          myTimer.clear();
          Controller1.Screen.clearScreen();
          Controller1.Screen.setCursor(1,1);
          Controller1.Screen.print("playback");
          int foo=0;
          //Controller1.Screen.setCursor(1,1);
          //Controller1.Screen.print("Robot Autonomous");
          //Controller1.Screen.setCursor(2,1);
           
          wakeTime = double (pulse); 
          
        
          restTime= myTimer.time(timeUnits::msec); 
         ReadFromSDcard();
         while(foo<RobotLife)
          {
            
         sleepTime= myTimer.time(timeUnits::msec);     
        
             
            
          if (sleepTime>=wakeTime)
          {
           // Controller1.Screen.setCursor(3,1);
           // Controller1.Screen.print((wakeTime-restTime)); 
           //spin the motors using value data 1 and data 2
          for(int i = 0; i < 8; i++)
         {  Button[i] = ((DataThree[foo] >> i & 0x01)); }
         

         if (Button[2]){
            Stacker.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
            
        }
         if (Button[3]){
            Stacker.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
        }
        
        if (!Button[2] && !Button[3]  )
        {
            Stacker.stop(vex::brakeType::brake);
           
        }
        if (Button[6]){
          ZeroStacker(); 
        }
        
        if (Button[7]){
          if (StackerState==0){
            Stacker.rotateFor(1700,rotationUnits::deg,80, vex::velocityUnits::pct);
            StackerState=1;
          }
          else {
            Controller1.rumble("..");
          }          
        }
        // Arm's Code
        if (Button[5]){
            Arm.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
             
            
            
        }
         if (Button[4]){
            Arm.spin(vex::directionType::rev,127, vex::velocityUnits::pct);
            
        }
        
        if (!Button[4] && !Button[5]  )
        {
            Arm.stop(vex::brakeType::hold);
        }
        
       
        
        // Roller's Code
        if(Button[0]) 
        {
            Roller1.spin(vex::directionType::rev, 70, vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
        }
        if(Button[1]) 
        {
            Roller1.spin(vex::directionType::fwd, 50 , vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
        }
        if (!Button[1] && !Button[0] )
        { 
            Roller1.stop(vex::brakeType::hold);
            Roller2.stop(vex::brakeType::hold);
        }
            one = DataOne[foo]-127; 
            two = DataTwo[foo]-127;
            four = DataFour[foo]-127;
        
            if (four){
        RL.spin(vex::directionType::rev,four,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,four,vex::velocityUnits::pct);
        FR.spin(vex::directionType::rev,four,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,four,vex::velocityUnits::pct);
}
else{
            speedFL=   two + one;
            speedFR =  two -one;
            speedRR =  two -one;
            speedRL =  two +one;
       
       
            
        
        RL.spin(vex::directionType::fwd,speedRL,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,speedRR,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,speedFR,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,speedFL,vex::velocityUnits::pct);
}
            foo++;   
            
                
            wakeTime += double(pulse);
                
            restTime = myTimer.time(timeUnits::msec); 
              
         }
        }       
       }

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.


    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.
 if (Controller1.ButtonR1.pressing()){
            Stacker.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);        
        }
         if (Controller1.ButtonR2.pressing()){
            Stacker.spin(vex::directionType::fwd, 127, vex::velocityUnits::pct);
        }
        
        if (!Controller1.ButtonR1.pressing() && !Controller1.ButtonR2.pressing()  )
        {
            Stacker.stop(vex::brakeType::brake);
           
        }

        if (!Controller1.ButtonR1.pressing() && !Controller1.ButtonR2.pressing()  )
        {
            Stacker.stop(vex::brakeType::brake);
           
        }
        
        if (Controller1.ButtonDown.pressing()){
          ZeroStacker(); 
        }
        
        if (Controller1.ButtonB.pressing()){
          if (StackerState==0){
            Stacker.rotateFor(1650,rotationUnits::deg,80, vex::velocityUnits::pct);
            StackerState=1;
          }
          else {
            Controller1.rumble("..");
          }          
        }
       
        
    
        
        
        // Arm's Code
        if (Controller1.ButtonL2.pressing()){
            Arm.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
             
            
            
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
            Roller1.spin(vex::directionType::rev,70 , vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::fwd,70, vex::velocityUnits::pct);
        }
        if(Controller1.ButtonY.pressing()) 
        {
            Roller1.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
        }
        if (!Controller1.ButtonRight.pressing() && !Controller1.ButtonY.pressing()  )
        { 
            Roller1.stop(vex::brakeType::hold);
            Roller2.stop(vex::brakeType::hold);
        }
        
        
        
        
         //driveBase
         two= Controller1.Axis2.value();//movement
         one = Controller1.Axis1.value(); //rotation
         four=Controller1.Axis4.value();
      
        
           
       
            speedFL=   two + one;
            speedFR =  two -one;
            speedRR =  two -one;
            speedRL =  two +one;
        RL.spin(vex::directionType::fwd,speedRL,vex::velocityUnits::pct);
        RR.spin(vex::directionType::fwd,speedRR,vex::velocityUnits::pct);
        FR.spin(vex::directionType::fwd,speedFR,vex::velocityUnits::pct);
        FL.spin(vex::directionType::fwd,speedFL,vex::velocityUnits::pct);
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