/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Tank Drive                                                */
/*    This sample allows you to control the V5 Clawbot using the both         */
/*    joystick. Adjust the deadband value for more accurate movements.        */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// LeftMotor            motor         1
// RightMotor           motor         10
// ClawMotor            motor         3
// ArmMotor             motor         8
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>

using namespace vex;

bool tripleNutBool = false;
int speed = 100;
int flywheelDesiredSpeed = 60;

void IntakeFwd() {
  Intake.spin(forward);
  // Roller.setVelocity(65, percent);
  Roller.spin(reverse);
  // waitUntil(!Controller1.ButtonX.pressing());
  // Intake.stop();
}

void IntakeRev() {
  Intake.spin(reverse);
  Roller.spin(forward);
  waitUntil(!Controller1.ButtonY.pressing());
  Intake.stop();
  Roller.stop();
}

int getFlywheelSpeed() {
  return (Flywheel1.velocity(pct) + Flywheel2.velocity(pct)) / 2;
}

void FlywheelFwd() {
  Flywheel1.spin(forward);
  Flywheel2.spin(forward);
  while(Controller1.ButtonL2.pressing()) {
    if(getFlywheelSpeed() < flywheelDesiredSpeed) {
      Flywheel1.setVelocity(flywheelDesiredSpeed + flywheelDesiredSpeed - getFlywheelSpeed(), pct);
      Flywheel2.setVelocity(flywheelDesiredSpeed + flywheelDesiredSpeed - getFlywheelSpeed(), pct);
    }
    else {
      Flywheel1.setVelocity(flywheelDesiredSpeed - (flywheelDesiredSpeed - getFlywheelSpeed()), pct);
      Flywheel2.setVelocity(flywheelDesiredSpeed - (flywheelDesiredSpeed - getFlywheelSpeed()), pct);
    }
    task::sleep(20);
  }

  waitUntil(!Controller1.ButtonL2.pressing());
  Flywheel1.stop(brakeType::coast);
  Flywheel2.stop(brakeType::coast);
}

void RollerFwd() {
  Roller.spin(forward);
  waitUntil(!Controller1.ButtonR1.pressing());
  Roller.stop();
}

void fire() {
  piston.set(!piston);
  task::sleep(50);
  piston.set(!piston);
}

void tripleNut() {
  if(tripleNutBool == true) {
    endgame.set(!endgame);
  }
}

void tripleNutCheck() {
  tripleNutBool = true;
  task::sleep(100);
}

void printTemp() {
  printf("Motor Temp %f " , Flywheel1.temperature(temperatureUnits::fahrenheit));
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Deadband stops the motors when Axis values are close to zero.
  int deadband = 2;

  Intake.setStopping(hold);
  Intake.setVelocity(100, percent);
  Flywheel1.setStopping(hold);
  Flywheel1.setVelocity(flywheelDesiredSpeed, percent);
  Flywheel1.setStopping(hold);
  Flywheel2.setVelocity(flywheelDesiredSpeed, percent);
  Roller.setVelocity(100, percent);
  Roller.setStopping(hold);

  FrontLeft.setStopping(coast);
  MiddleLeft.setStopping(coast);
  BackLeft.setStopping(coast);

  FrontRight.setStopping(coast);
  MiddleRight.setStopping(coast);
  BackRight.setStopping(coast);

  FrontLeft.setBrake(coast);
  FrontRight.setBrake(coast);
  BackLeft.setBrake(coast);
  BackRight.setBrake(coast);

  Controller1.ButtonY.pressed(IntakeRev);
  Controller1.ButtonL1.pressed(IntakeFwd);
  Controller1.ButtonL2.pressed(FlywheelFwd);
  Controller1.ButtonR1.pressed(RollerFwd);
  Controller1.ButtonR2.pressed(fire);
  Controller1.ButtonRight.pressed(tripleNut);
  Controller1.ButtonLeft.pressed(tripleNutCheck);
  
  Brain.Screen.drawImageFromFile("MonkeyFlagFinal.png", 0, 0);
  Brain.Screen.render();

  Brain.Screen.drawImageFromFile("TEAMMONKEY.png", 0, 0);
  Brain.Screen.render();

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  
  while (true) {
    Controller1.Screen.print("Motor Temp %f " , FrontLeft.temperature(temperatureUnits::fahrenheit));
  
    int leftMotorSpeed;
    int rightMotorSpeed;

    // printf("Motor Temp %f " , FrontRight.temperature(temperatureUnits::fahrenheit));

    // printf("Motor Temp %f " , Flywheel1.temperature(temperatureUnits::fahrenheit));
    // Get the velocity percentage of the left motor. (Axis3)
    leftMotorSpeed  = (Controller1.Axis3.position() + Controller1.Axis1.position()) * .50;
    // Get the velocity percentage of the right motor. (Axis3 - Axis1)
    rightMotorSpeed = (Controller1.Axis3.position() - Controller1.Axis1.position()) * .50;
    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.

    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      FrontLeft.setVelocity(0, percent);
      MiddleLeft.setVelocity(0, percent);
      BackLeft.setVelocity(0, percent);

      FrontLeft.stop(brakeType::coast);
      MiddleLeft.stop(brakeType::coast);
      BackLeft.stop(brakeType::coast);
    } else {
      // Set the speed to leftMotorSpeed
      FrontLeft.setVelocity(leftMotorSpeed, percent);
      MiddleLeft.setVelocity(leftMotorSpeed, percent);
      BackLeft.setVelocity(leftMotorSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      FrontRight.setVelocity(0, percent);
      MiddleRight.setVelocity(0, percent);
      BackRight.setVelocity(0, percent);

      FrontRight.stop(brakeType::coast);
      MiddleRight.stop(brakeType::coast);
      BackRight.stop(brakeType::coast);
    } else {
      // Set the speed to rightMotorSpeed
      FrontRight.setVelocity(rightMotorSpeed, percent);
      MiddleRight.setVelocity(rightMotorSpeed, percent);
      BackRight.setVelocity(rightMotorSpeed, percent);
    }

    // Spin both motors in the forward direction.
    FrontLeft.spin(forward);
    MiddleLeft.spin(forward);
    BackLeft.spin(forward);
    
    FrontRight.spin(forward);
    MiddleRight.spin(forward);
    BackRight.spin(forward);

    wait(25, msec);
  }
}
