#pragma config(Sensor, dgtl5,  mobileGoalLimitSwitch, sensorTouch)
#pragma config(Motor,  port1,           M_MOBILE_GOAL_LIFT, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           M_WHEEL_R2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           M_WHEEL_R1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           M_WHEEL_L1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           M_WHEEL_L2,    tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
  MAIN.C
  Primary file: Holds the entire competition sequence. You compile and flash THIS file.
  Jeffrey Shen
*/

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(1200)

#include "Vex_Competition_Includes.c"
#include "parallax-lib/bin/constants.h"
#include "parallax-lib/bin/functions.c"
#include "main.h"
#include "mobile_goal.c"
#include "config.c"

void pre_auton(){

}

task autonomous(){

}

/*
	USER CONTROL
*/

task usercontrol(){
  int V, H;

  while(true){

    V = vexRT[Ch3];
		H = vexRT[Ch1];

		if (abs(V) < 15) V = 0;
		if (abs(H) < 15) H = 0;
		move(V, H, 0);

    if(vexRT[Btn6U] == 1){
      moveMobileGoalLift(UP);
    }
    else if(vexRT[Btn6D] == 1){
      moveMobileGoalLift(DOWN);
    }
    else{
      moveMobileGoalLift(STOP);
    }

		wait1Msec(10);
	}
}
