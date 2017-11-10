#ifndef MAIN_H
#define MAIN_H

/*
  MAIN.H
  Holds various variables and wrapper functions
*/

// ** Wrapper functions **

//Mobile Goal
void moveMobileGoalLift(int status);
int mobileGoalIsInPlace();
void automaticMobileGoalLift();

//Cone lift
void moveClaw(int status);
void openClaw();
void closeClaw();
void moveLift();

//Auton

// ** Constants **
#define CONE_LIFT1_MAX_V 127
#define CONE_LIFT1_MIN_V -127
#define CONE_LIFT1_DEFAULT_V 0
#define CONE_LIFT1_KX 0.45
#define CONE_LIFT1_KV 0.01

#define CONE_LIFT2_MAX_V 127
#define CONE_LIFT2_MIN_V -127
#define CONE_LIFT2_DEFAULT_V 20
#define CONE_LIFT2_KX -0.5
#define CONE_LIFT2_KV 0

#define BASE_LEFT_KP 1
#define BASE_LEFT_KD 1
#define BASE_RIGHT_KP 1
#define BASE_RIGHT_KD 1
#define GYRO_KP 1
#define GYRO_KD 1


// ** Custom Easy Names **
#define DOWN_WITHOUT_GOAL 10

// ** Global variables **
#define PRESET 20
int clawIsClosed = 0;
int clawIsOpened = 0;
int coneNum = 0;
int liftVal;
int currentlyCarrying = 0;
int secondJointHasStalled = 0;

//Command Flags
int MOBILE_GOAL_COMMAND = 0;
int CONE_LIFT_COMMAND = 0;

//Debug flags
#define DEBUG_CONE_LIFT 1
#define DEBUG_MOBILE_GOAL 1

#endif
