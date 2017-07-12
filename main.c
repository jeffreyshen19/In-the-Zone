#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    PWR,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,  wheelEncoderLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  wheelEncoderRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  mobileGoalLimitSwitch, sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           M_MOBILE_GOAL_LIFT, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           M_WHEEL_R2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           M_WHEEL_R1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           M_TURNTABLE,   tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port5,           M_FIRST_LIFT1, tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           M_FIRST_LIFT2, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           M_SECOND_LIFT, tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port8,           M_WHEEL_L1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           M_WHEEL_L2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          M_CLAW,        tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_4)
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
#include "main.h"
#include "parallax-lib/main.c"
#include "mobile_goal.c"
#include "cone_lift.c"

void pre_auton(){
	nMotorEncoder[M_CLAW] = 0;
	nMotorEncoder[M_TURNTABLE] = 0;
	bStopTasksBetweenModes = false;
	startTask(mobileGoalTask, 9);
	initialize();
}

task autonomous(){
	stopTask(usercontrol);
	autonProcedure();
}

/*
	USER CONTROL
*/

task usercontrol(){
  int V, H;

  stopTask(autonomous);

  playSoundFile("yeahboi.wav");

  while(true){

    V = vexRT[Ch3];
		H = vexRT[Ch1];

		if (abs(V) < 15) V = 0;
		if (abs(H) < 15) H = 0;
		move(V, H, 0);

    if(vexRT[Btn6U] == 1){
      MOBILE_GOAL_COMMAND = UP;
    }
    else if(vexRT[Btn6D] == 1){
      MOBILE_GOAL_COMMAND = DOWN;
    }
		else if(vexRT[Btn7L] == 1){
			MOBILE_GOAL_COMMAND = DOWN_WITHOUT_GOAL;
		}

    if(vexRT[Btn5U] == 1){
      moveTurntableBy(450, CLOCKWISE, 2000);
    }
    else if(vexRT[Btn5D] == 1){
      moveTurntableBy(450, COUNTERCLOCKWISE, 2000);
    }
    else{
      moveTurntable(STOP);
    }

    if(vexRT[Btn7U] == 1){
      moveFirstLiftJoint(UP);
    }
    else if(vexRT[Btn7D] == 1){
      moveFirstLiftJoint(DOWN);
    }
    else{
      moveFirstLiftJoint(STOP);
    }

		if(vexRT[Btn7L] == 1){
      moveSecondLiftJoint(UP);
    }
    else if(vexRT[Btn7R] == 1){
      moveSecondLiftJoint(DOWN);
    }
    else{
      moveSecondLiftJoint(STOP);
    }

    if(vexRT[Btn8U] == 1){
      openClaw();
    }
    else if(vexRT[Btn8D] == 1){
      closeClaw():
    }
    else if(clawIsClosed){
    	moveClaw(10);
    }

		userControlUpdate();
	}
}
