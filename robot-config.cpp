#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// VEXcode device constructors

motor FrontLeft = motor(PORT13, ratio18_1, true);
motor MiddleLeft = motor(PORT11, ratio18_1, false);
motor BackLeft = motor(PORT12, ratio18_1, true);

motor FrontRight = motor(PORT19, ratio18_1, false);
motor MiddleRight = motor(PORT20, ratio18_1, true);
motor BackRight = motor(PORT18, ratio18_1, false);

motor Intake = motor(PORT1, ratio18_1, true);

motor Flywheel1 = motor(PORT16, ratio18_1, true);
motor Flywheel2 = motor(PORT17, ratio18_1, false);

controller Controller1 = vex::controller();


digital_out piston = digital_out(Brain.ThreeWirePort.A);
digital_out endgame = digital_out(Brain.ThreeWirePort.B);

motor Roller = motor(PORT13, ratio18_1, true);

inertial Inertial12 = inertial(PORT12);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}
