#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor front_right = motor(PORT1, ratio18_1, false);
motor front_left = motor(PORT8, ratio18_1, true);
motor back_left = motor(PORT9, ratio18_1, true);
motor back_right = motor(PORT2, ratio18_1, false);
controller Controller1 = controller(primary);
motor left_intake = motor(PORT3, ratio18_1, false);
motor right_intake = motor(PORT7, ratio18_1, true);
motor arms = motor(PORT14, ratio18_1, true);
motor ramp = motor(PORT10, ratio18_1, false);
pot Potentiometer = pot(Brain.ThreeWirePort.H);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}