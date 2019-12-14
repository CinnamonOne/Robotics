// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         1               
// front_left           motor         8               
// back_left            motor         9               
// back_right           motor         2               
// Controller1          controller                    
// left_intake          motor         3               
// right_intake         motor         7               
// arms                 motor         14              
// Vision               vision        13              
// Potentiometer        pot           A               
// Ultrasonic           sonar         C, D            
// ramp                 motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\efrag                                            */
/*    Created:      Thu Oct 03 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "robot-config.h"
#include "frame-class.h"

using namespace vex;

competition Competition;

// Base Variables
int speedBase = 85;
int speed = speedBase;
int speedWave = 0;

// Distance Variables
float rotations = 360;
double first_tile = rotations*2.5;
double one_tile = rotations*1.9; 

// Base Movement
void basevelocity(double n)
{
  front_left.setVelocity(n, percent);
  front_right.setVelocity(n, percent);
  back_right.setVelocity(n, percent);
  back_left.setVelocity(n, percent);
}
void GO(double n)
{
  front_right.rotateFor(n, turns, false);
  back_right.rotateFor(n, turns, false);
  front_left.rotateFor(n, turns, false);
  back_left.rotateFor(n, turns);
}
void turnfor(double n) 
{
  front_right.rotateFor(n, degrees, false);
  back_right.rotateFor(n, degrees, false);
  front_left.rotateFor(-n, degrees, false);
  back_left.rotateFor(-n, degrees);
}

// Distance Movement
void move_firsttile(double t)
{
  front_right.rotateFor(first_tile*t, deg, false);
  back_right.rotateFor(first_tile*t, deg, false);
  front_left.rotateFor(first_tile*t, deg, false);
  back_left.rotateFor(first_tile*t, deg);
}
void move_onetile(double t)
{
  front_right.rotateFor(one_tile*t, deg, false);
  back_right.rotateFor(one_tile*t, deg, false);
  front_left.rotateFor(one_tile*t, deg, false);
  back_left.rotateFor(one_tile*t, deg, false);
}

// Ramp Movement
void rampUp()
{
  ramp.spin(forward);
}
void rampDown()
{
  ramp.spin(reverse);
}
void rampStop() 
{
  ramp.setVelocity(0, percent);
  ramp.spin(forward);
}
// Variable for times pressed button
int ramp_vel = 75;
int xPressed = 0;
// Function for times pressed button
void timespressed(){
  xPressed++;
  Controller1.Screen.clearScreen();
  Controller1.Screen.print("Times Pressed");
}
void(minus10()){
  if(ramp_vel > 10){
      ramp_vel -= 10;
      Controller1.Screen.clearScreen();
      Controller1.Screen.print("Current Vel is =>", ramp_vel);
  }
}
void(plus10()){
  if(ramp_vel < 90){
    ramp_vel += 10;
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("Current Vel is =>", ramp_vel);
  }
}

// Arms Movement
void up()
{
  arms.setVelocity(100,percent);
  arms.spin(forward);
}
void down()
{
  arms.setVelocity(50,percent);
  arms.spin(reverse);
}

// Intake Movement
void intake()
{
  left_intake.spin(forward);
  right_intake.spin(forward);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("IN");
}
void outtake()
{
  left_intake.spin(reverse);
  right_intake.spin(reverse);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("OT");
}
void stoptake()
{
  left_intake.setVelocity(0, percent);
  right_intake.setVelocity(0, percent);
  left_intake.spin(forward);
  right_intake.spin(forward);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("NE");
}

void pre_auton()
{
  // WE USE THIS SECTION FOR TRASHED AUTONS / EXPERIMENTAL STUFF =>

  /* Go Forward Auton (safe 1 point)
  double vel = 100*0.75;

  front_left.setVelocity(vel, percent);
  back_right.setVelocity(vel, percent);
  back_left.setVelocity(vel, percent);
  front_right.setVelocity(vel, percent);

  front_left.spin(forward);
  front_right.spin(forward);
  back_left.spin(forward);
  back_right.spin(forward);

  vex::task::sleep(3500);

  front_left.spin(reverse);
  front_right.spin(reverse);
  back_left.spin(reverse);
  back_right.spin(reverse);

  vex::task::sleep(3000);*/


  /* Vision Sensor checking for color
  event checkPurple = event();

  void hasPurpleCallback()
  {
	  Brain.Screen.setFont(mono40);
	  Brain.Screen.clearLine(1, purple);
	  Brain.Screen.setCursor(Brain.Screen.row(), 1);
	  Brain.Screen.setCursor(1, 1);
	  Vision.takeSnapshot(Vision__PURPLE_CUBE);
	  if(Vision.objectCount > 0) {
		  Brain.Screen.print("CUBE CUBE CUBE PURPLE YES GOOD");
	  } else {
		  Brain.Screen.print("No cube");
	  }
  }*/
}

void autonomous()
{
  /* !!!!THIS AUTON HAS NOT BEEN TESTED!!!!

  // 1 tile movement is 2.32 rotations
  // The first tile movement is 2.08 rotations
  // To change amount of tiles moved, t (the amount of tiles you want to move) will be multiplied by 2.32 or 2.08

  // Set Base Velocity 75%
  basevelocity(75);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("75% Velocity");

  // Move to put block in square & back
  move_onetile(1);
  move_onetile(-1);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Forward & Back");

  // Turn 90 degrees to look at 4 blocks | wall safety | lift arms
  turnfor(90);
  GO(-0.5);
  arms.spin(forward);

  vex::task::sleep(2000); // Arms spin for 2 seconds

  arms.spin(reverse);

  vex::task::sleep(2000);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Prepare Intake");

  // Go forward and intake 4 blocks | Go back for safety at slow speed
  intake();
  move_firsttile(1);
  move_onetile(1);

  vex::task::sleep(100);

  basevelocity(30);
  move_onetile(-1);
  Controller1.Screen.clearLine();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Auton Finished");*/
}

void usercontrol() 
{
  while (1) {

    //Brain.Screen.print("I AM WORKING YEEEEEEEEE!");
    
    float Axis1 = -Controller1.Axis1.value();
    float Axis2 = -Controller1.Axis2.value();
    float Axis3 =  Controller1.Axis3.value();
    float Axis4 = -Controller1.Axis4.value();

    if (abs(Axis3) > 0 && speedWave < 100) {
      speedWave += 2;
    } else {
      speedWave -= ((speedWave > 0) ? 2 : 0);
    }

    front_left.setVelocity(50, percent);
    back_right.setVelocity(50, percent);
    back_left.setVelocity(50, percent);
    front_right.setVelocity(50, percent);

    front_left.spin(directionType::fwd, Axis3 - Axis1, velocityUnits::pct);
    back_left.spin(directionType::fwd, Axis3 - Axis1, velocityUnits::pct);

    front_right.spin(directionType::fwd, Axis3 + Axis1, velocityUnits::pct);
    back_right.spin(directionType::fwd, Axis3 + Axis1, velocityUnits::pct);
    
    // Arms
    if(Controller1.ButtonL2.pressing()) {up();}
    else if (Controller1.ButtonL1.pressing()) {down();}
    else {arms.stop();} 
    
    // Intake / Outtake
    left_intake.setVelocity(100, percent);
    right_intake.setVelocity(100, percent);
    if(Controller1.ButtonR2.pressing()) {
      left_intake.setVelocity(50, percent);
      right_intake.setVelocity(50, percent);
      outtake();
    }
    else if (Controller1.ButtonR1.pressing()) {intake();}
    else {stoptake();}

    // Ramp
    ramp.setVelocity(ramp_vel, percent);
    if(Controller1.ButtonUp.pressing()){
      rampUp();
    }
    else if(Controller1.ButtonDown.pressing()){
      rampDown();
    }
    else{
      rampStop();
    }
    // Ramp Velocity
    Controller1.ButtonLeft.pressed(minus10);
    Controller1.ButtonRight.pressed(plus10);

    if (Controller1.ButtonB.pressing()) {
      Controller1.Screen.clearLine();
      Controller1.Screen.print(round(Potentiometer.angle(degrees)*1.005)-1);
    }
    if (Controller1.ButtonA.pressing()) {
      speed = 100;
    } else {
      speed = speedBase;
    }

    task::sleep(20);
  }
}

int main() {

    vexcodeInit();

    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }
       
}