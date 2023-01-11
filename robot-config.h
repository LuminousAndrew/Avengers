using namespace vex;

extern brain Brain;

extern motor FrontLeft;
extern motor MiddleLeft;
extern motor BackLeft;

extern motor FrontRight;
extern motor MiddleRight;
extern motor BackRight;

extern motor Intake;

extern motor Flywheel1;
extern motor Flywheel2;

extern controller Controller1;

extern digital_out piston;
extern digital_out endgame;

extern motor Roller;

extern inertial Inertial12;

extern smartdrive Drivetrain;
extern gps GPS8;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
