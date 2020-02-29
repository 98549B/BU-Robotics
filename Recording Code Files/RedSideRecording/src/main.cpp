#include "vex.h"
#define pulse 100         
#define RobotLife 150  
#define MaxTorque 0.9
    
   /////////////////////////////////// Start of Functions and Variables ////////////////////////////////////////////////////
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
void DDS(int boo, int R1, int R2, int R3, int R4){ //DDS is Data Diagnostics Screen
           Controller1.Screen.setCursor(1,10);
            Controller1.Screen.print(boo);
                Controller1.Screen.setCursor(2,1);
              Controller1.Screen.print(R1);
                Controller1.Screen.setCursor(2,10);
                Controller1.Screen.print(R2);
                Controller1.Screen.setCursor(3,1);
                Controller1.Screen.print(R3);
                Controller1.Screen.setCursor(3,10);
                Controller1.Screen.print(R4);
    }


void MDS(int boo){ //MDS is Motor Diagnostics Screen
           Controller1.Screen.setCursor(1,10);
            Controller1.Screen.print(boo);
                Controller1.Screen.setCursor(2,1);
              Controller1.Screen.print(FL.rotation(rotationUnits::deg));
                Controller1.Screen.setCursor(2,10);
                Controller1.Screen.print(FR.rotation(rotationUnits::deg));
                Controller1.Screen.setCursor(3,1);
                Controller1.Screen.print(RL.rotation(rotationUnits::deg));
                Controller1.Screen.setCursor(3,10);
                Controller1.Screen.print(RR.rotation(rotationUnits::deg));
    }


void FlushToSDcard (){ //Start of FlushToSDcard

    // write test data to SD Card
    int DataOneWritten = Brain.SDcard.savefile( "dataOne.Red", DataOne, sizeof(DataOne) );
    int DataTwoWritten = Brain.SDcard.savefile( "dataTwo.Red", DataTwo, sizeof(DataTwo) );
    int DataThreeWritten = Brain.SDcard.savefile( "dataThree.Red", DataThree, sizeof(DataThree) );
    int DataFourWritten = Brain.SDcard.savefile( "dataFour.Red", DataFour, sizeof(DataFour) );
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
        int ReadOne = Brain.SDcard.loadfile( "dataOne.Red", DataOne, sizeof(DataOne) );
        int ReadTwo = Brain.SDcard.loadfile( "dataTwo.Red", DataTwo, sizeof(DataTwo) );
        int ReadThree = Brain.SDcard.loadfile( "dataThree.Red", DataThree, sizeof(DataThree));
        int ReadFour = Brain.SDcard.loadfile( "dataFour.Red", DataFour, sizeof(DataFour));
        // display on screen how many bytes we read
        Brain.Screen.setCursor( 3, 2 );
        Brain.Screen.print( "We read %d bytes from the SD Card", (ReadOne+ReadTwo+ReadThree+ReadFour) );
  
  }//End of ReadFromSDcard


//////////////////////////////////////// End of Functions and Variables /////////////////////////////////////////////////////// 

int main() { /// Start of int Main

    
    
    Controller1.Screen.clearScreen();
    
    while (1)      
    {
     
     if(Controller1.ButtonX.pressing())
      {
      //Pressing button X plays the Auto 
      
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
            Stacker.spin(vex::directionType::rev, 127, vex::velocityUnits::pct);
            
        }
         if (Button[3]){
            Stacker.spin(vex::directionType::fwd,127, vex::velocityUnits::pct);
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
           Stacker.rotateFor(650,rotationUnits::deg,127, vex::velocityUnits::pct);
            Stacker.rotateFor(650,rotationUnits::deg,50, vex::velocityUnits::pct);
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
            Roller1.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
        }
        if(Button[1]) 
        {
            Roller1.spin(vex::directionType::fwd, 70 , vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::rev, 70, vex::velocityUnits::pct);
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

              
      if(Controller1.ButtonA.pressing())    //RECORD
      { 
          //Pressing button A records 
          task::sleep(1000);
          Controller1.rumble(".");
          task::sleep(1000);
          Controller1.Screen.clearScreen();
          Controller1.Screen.setCursor(1,1);
          Controller1.Screen.print("Recording");
          robotCycle = 0;
          isRecording = 1; 
          myTimer.clear();
          wakeTime=pulse;
         

         while(robotCycle<RobotLife){
                 
         sleepTime= myTimer.time(timeUnits::msec); 
            
         if (sleepTime >= wakeTime)
         {

        Button[0] = Controller1.ButtonRight.pressing();
        Button[1] = Controller1.ButtonY.pressing();
        Button[2] = Controller1.ButtonR1.pressing();
        Button[3] = Controller1.ButtonR2.pressing();
        Button[4] = Controller1.ButtonL1.pressing();
        Button[5] = Controller1.ButtonL2.pressing();
        Button[6] = Controller1.ButtonDown.pressing();
        Button[7] = Controller1.ButtonB.pressing();
       
        DataThree[robotCycle] = ( Button[0]*1 + Button[1]*2 + Button[2]*4 + Button[3]*8 + Button[4]*16 + Button[5]*32 + Button[6]*64 + Button[7]*128) ;   
       
  
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
           Stacker.rotateFor(650,rotationUnits::deg,127, vex::velocityUnits::pct);
            Stacker.rotateFor(650,rotationUnits::deg,50, vex::velocityUnits::pct);
            StackerState=1;
          }
          else {
            Controller1.rumble("..");
          }          
        }
       
         
        
        
    
        
        // Arm's Code
        if (Button[5]){
            Arm.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);      
        }
         if (Button[4]){
            Arm.spin(vex::directionType::rev,127, vex::velocityUnits::pct); 
        }
        
        if (!Button[4] && !Button[5])
        {
            Arm.stop(vex::brakeType::hold);
        }
        
       
        
        // Roller's Code
        if(Button[0]) 
        {
            Roller1.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        }
        if(Button[1]) 
        {
            Roller1.spin(vex::directionType::fwd, 70 , vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::rev, 70, vex::velocityUnits::pct);
        }
        if (!Button[1] && !Button[0] )
        { 
            Roller1.stop(vex::brakeType::hold);
            Roller2.stop(vex::brakeType::hold);
        }
         one = Controller1.Axis1.value(); //rotation
         two= Controller1.Axis2.value();//movement
         four = Controller1.Axis4.value();
                  
        DataOne[robotCycle] = one+127;
        DataTwo[robotCycle] = two+127;
         DataFour[robotCycle] = four+127; 
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
        
           wakeTime+=pulse;           
           robotCycle++; 
             
         
                 
         }

         }    
        
        
         
      //flush to sd card // clear scrn , print save to sd card
          FlushToSDcard();
          Controller1.Screen.clearScreen();
          Controller1.Screen.setCursor(1,1);
          Controller1.Screen.print("Saved to SD Card");
          
      }
        
        
        
   else {
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

        
        if (Controller1.ButtonDown.pressing()){
          ZeroStacker(); 
        }
        
        if (Controller1.ButtonB.pressing()){
          if (StackerState==0){
            Stacker.rotateFor(650,rotationUnits::deg,127, vex::velocityUnits::pct);
            Stacker.rotateFor(650,rotationUnits::deg,50, vex::velocityUnits::pct);
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
            Roller1.spin(vex::directionType::rev,100 , vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        }
        if(Controller1.ButtonY.pressing()) 
        {
            Roller1.spin(vex::directionType::fwd, 70, vex::velocityUnits::pct);
            Roller2.spin(vex::directionType::rev, 70, vex::velocityUnits::pct);
        }
        if (!Controller1.ButtonRight.pressing() && !Controller1.ButtonY.pressing()  )
        { 
            Roller1.stop(vex::brakeType::hold);
            Roller2.stop(vex::brakeType::hold);
        }
        
        
        
        
         //driveBase
         two= Controller1.Axis2.value();//movement
         one = Controller1.Axis1.value(); //rotation
         four = Controller1.Axis4.value();
      
        
           
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
     } 
        
    }
   }
   
 // End of int Main 
