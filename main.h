#ifndef MAIN_H
#define MAIN_H

/*
  MAIN.H
  Holds various variables and wrapper functions
*/


//Wrapper functions

//Mobile Goal
void moveMobileGoalLift(int status);
int mobileGoalIsInPlace();
void automaticMobileGoalLift();

//Cone lift
void moveTurntable(int val);
void moveFirstLiftJoint(int status);
int getTurntableValue();
void moveTurntableBy(int degrees, int status);
void moveClaw(int status);
void moveSecondLiftJoint(int status);
int getFirstLiftValue();
int getSecondLiftValue();
void openClaw();
void closeClaw();

#endif
