#ifndef MAIN_H
#define MAIN_H

/*
  MAIN.H
  Holds various variables and wrapper functions
*/

// ** Custom Easy Names **
#define DOWN_WITHOUT_GOAL 10

// ** Global variables **

int clawIsClosed = 0;

//Command Flags
int MOBILE_GOAL_COMMAND = STOP;

// ** Wrapper functions **

//Mobile Goal
void moveMobileGoalLift(int status);
int mobileGoalIsInPlace();
void automaticMobileGoalLift();

//Cone lift
void moveTurntable(int val);
void moveFirstLiftJoint(int status);
int getTurntableValue();
int getTurntableDegrees();
void moveTurntableBy(int degrees, int status, int tlimit);
void moveTurntableToGoal();
void moveTurntableToFront();
void moveClaw(int status);
void moveSecondLiftJoint(int status);
int getFirstLiftValue();
int getSecondLiftValue();
void openClaw();
void closeClaw();

#endif
