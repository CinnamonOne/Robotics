// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         11              
// front_left           motor         20              
// back_left            motor         10              
// back_right           motor         1               
// Controller1          controller                    
// left_intake          motor         19              
// right_intake         motor         12              
// arm_right            motor         5               
// arm_left             motor         6               
// Vision               vision        13              
// Potentiometer        pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         11              
// front_left           motor         20              
// back_left            motor         10              
// back_right           motor         1               
// Controller1          controller                    
// left_intake          motor         19              
// right_intake         motor         12              
// arm_right            motor         5               
// arm_left             motor         6               
// Vision               vision        13              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         11              
// front_left           motor         20              
// back_left            motor         10              
// back_right           motor         1               
// Controller1          controller                    
// left_intake          motor         19              
// right_intake         motor         12              
// arm_right            motor         5               
// arm_left             motor         6               
// Vision13             vision        13              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// front_right          motor         11              
// front_left           motor         20              
// back_left            motor         10              
// back_right           motor         1               
// Controller1          controller                    
// left_intake          motor         19              
// right_intake         motor         12              
// arm_right            motor         5               
// arm_left             motor         6               
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
   
void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

void turnFor(double n) {
  front_right.spinFor(n, degrees);
  back_right.spinFor(n, degrees);
  front_left.spinFor(-n, degrees);
  back_left.spinFor(-n, degrees);
}

void basevelocity(double n){
  front_left.setVelocity(n, percent);
  front_right.setVelocity(n, percent);
  back_right.setVelocity(n, percent);
  back_left.setVelocity(n, percent);
}

void goForward(double n) {
  front_right.spinFor(n, turns);
  back_right.spinFor(n, turns);
  front_left.spinFor(n, turns);
  back_left.spinFor(n, turns);
}

void up() {
  arm_left.spin(reverse);
  arm_right.spin(reverse);
}
void down(){
  arm_left.spin(forward);
  arm_right.spin(forward);
}

void intake(){
  left_intake.spin(reverse);
  right_intake.spin(reverse);
}
void outtake(){
  left_intake.spin(forward);
  right_intake.spin(forward);
}
void stoptake() {
  left_intake.stop();
  right_intake.stop();
}

event checkPurple = event();

void hasPurpleCallback() {
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
}

void autonomous( void ) {
  /*

  */
}

void usercontrol( void ) {
  while (1) {
    
    float Axis1 = -Controller1.Axis1.value();
    float Axis2 = -Controller1.Axis2.value();
    float Axis3 = -Controller1.Axis3.value();
    float Axis4 = -Controller1.Axis4.value();

    if(Controller1.ButtonB.pressing()){
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("%.2f", Potentiometer.angle());
    }

    front_left.setVelocity(100, percent);
    back_right.setVelocity(100, percent);
    back_left.setVelocity(100, percent);
    front_right.setVelocity(100, percent);


    front_left.spin(directionType::fwd, Axis3 + Axis1, velocityUnits::pct);
    back_left.spin(directionType::fwd, Axis3 + Axis1, velocityUnits::pct);

    front_right.spin(directionType::fwd, Axis3 - Axis1, velocityUnits::pct);
    back_right.spin(directionType::fwd, Axis3 - Axis1, velocityUnits::pct);
// gamer moment
    arm_left.setVelocity(75,percent);
    arm_right.setVelocity(75,percent);
//b ruh
    if(Controller1.ButtonL2.pressing()) {up();}
    else if (Controller1.ButtonL1.pressing()) {down();}
    else {
      arm_left.stop();
      arm_right.stop();
    }
    
    left_intake.setVelocity(100, percent);
    right_intake.setVelocity(100, percent);

    if(Controller1.ButtonR2.pressing()) {intake();}
    else if (Controller1.ButtonR1.pressing()) {outtake();}
    else {stoptake();}

    
    if(Controller1.ButtonA.pressing()){

      Controller1.Screen.print("Brain A Is Woking");

    }

    task::sleep(20);
  }
}
//
// Main will set up the competition functions and callbacks.
//
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