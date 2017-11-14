#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    PWR,            sensorPotentiometer)
#pragma config(Sensor, in2,    Gyro,           sensorGyro)
#pragma config(Sensor, in3,    MobileGoal,     sensorPotentiometer)
#pragma config(Sensor, dgtl1,  wheelEncoderLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  wheelEncoderRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  mobileGoalLimitSwitch, sensorTouch)
#pragma config(Sensor, dgtl6,  secondLiftEncoder, sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  LIFT,           sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           M_MOBILE_GOAL_LIFT, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           M_WHEEL_R2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           M_WHEEL_R1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           M_LIFT_1,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           M_LIFT_2,      tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           M_LIFT_3,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           M_LIFT_4,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           M_WHEEL_L1,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           M_WHEEL_L2,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          M_CLAW,        tmotorVex393_HBridge, openLoop)
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
#include "parallax-lib/bin/constants.h"
#include "auton.c"

sensor liftSensor;
sensor baseLeft;
sensor baseRight;
sensor mobileGoalLift;
sensor gyro;
pid baseLeftPID;
pid baseRightPID;
pid gyroPID;
pid mobileGoalPID;

#include "parallax-lib/main.c"
#include "mobile_goal.c"
#include "cone_lift.c"

void pre_auton(){
	bStopTasksBetweenModes = false; //Make sure all tasks we create actually execute in user control

	startTask(mobileGoalTask, 9);
	startTask(coneLiftTask, 9);

	baseLeftPID.kp = BASE_LEFT_KP;
	baseLeftPID.kd = BASE_LEFT_KD;
	baseRightPID.kp = BASE_RIGHT_KP;
	baseRightPID.kd = BASE_RIGHT_KD;
	gyroPID.kp = GYRO_KP;
	gyroPID.kd = GYRO_KD;

	initializeSensor(&baseLeft, M_PI / 9.0, dgtl1, &baseLeftPID);
	initializeSensor(&baseRight, -1.0 * M_PI / 9, dgtl3, &baseRightPID);
	initializeSensor(&gyro, 1.0, in2, &gyroPID);

	makeLED(dgtl12, OFF);

	initializeDrive(0.0, &baseLeft, &baseRight, &gyro);
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
  int V, H, T, F, S;

  stopTask(autonomous);

  while(true){

		// ** Primary joystick **

  	V = vexRT[Ch3];
		H = vexRT[Ch1];

		if(abs(V) < 15) V = 0;
		if(abs(H) < 15) H = 0;
		move(V, H, 0);

    //Lift
		if(vexRT[Btn6U] == 1) CONE_LIFT_COMMAND = UP;
		else if(vexRT[Btn6D] == 1) CONE_LIFT_COMMAND = DOWN;
		else if(CONE_LIFT_COMMAND != PRESET) CONE_LIFT_COMMAND = STOP;

		//Claw
		if(vexRT[Btn5U] == 1) closeClaw();
		else if(vexRT[Btn5D] == 1) openClaw();

		if(clawIsClosed == 1){
			moveClaw(35);
		}
		else if(clawIsOpened == 1){
			moveClaw(-20);
		}

		if(vexRT[Btn8U] == 1){
			//Automatically raise to loader height
			liftVal = LOADER_HEIGHT;
			CONE_LIFT_COMMAND = PRESET;
		}
		else if(vexRT[Btn8D] == 1){
			//Automatically lower
			liftVal = 0;
			CONE_LIFT_COMMAND = PRESET;
		}

		//Mobile Goal
		if(vexRT[Btn7L] == 1) MOBILE_GOAL_COMMAND = DOWN;
		else if(vexRT[Btn7D] == 1) MOBILE_GOAL_COMMAND = UP;
		else if(vexRT[Btn7U] == 1) MOBILE_GOAL_COMMAND = DOWN_WITHOUT_GOAL;

		//YEAH BOIII :(
		if(getPrButton(Btn7R_Main) == PUSHED_RELEASED){
			//playSoundFile("yeahboi.wav");
			autoA();
			resetPrButton(Btn7R_Main);
		}

		userControlUpdate();
	}
}
