#ifndef CONE_LIFT_C
#define CONE_LIFT_C

#define SWING_ARM_MAX 265
#define SWING_ARM_MIN 5

/*
  CONE_LIFT.C
  Contains all the code for the cone claw and lift
*/

// ** Claw **
void moveClaw(int status){ //Manually opens and closes the claw
  if(status == CLOSE) moveClaw(127);
  else if(status == OPEN) moveClaw(-127);
  else motorReq[M_CLAW] = status;
}

void openClaw(){ //Automatically opens the claw
  int t0 = time1[T1];
  moveClaw(OPEN);
  clawIsClosed = 0;
  clawIsOpened = 1;
  while(!isTimedOut(t0 + 50)){
    moveClaw(OPEN);
    wait1Msec(10);
  }
  moveClaw(STOP);
}

void closeClaw(){ //Automatically closes the claw
  int t0 = time1[T1];
  moveClaw(CLOSE);
  clawIsClosed = 1;
  clawIsOpened = 0;
  while(!isTimedOut(t0 + 50)){
    moveClaw(CLOSE);
    wait1Msec(10);
  }
}

// ** Swinging Arm **
void moveSwingArm(int status){
  if(status == UP){
    moveSwingArm(127);
  }
  else if(status == DOWN){
    moveSwingArm(-127);
  }
  else motorReq[M_SWING_ARM] = status;
}

void swingArmUp(){
	int t0 = time1[T1];
  moveSwingArm(UP);
  swingArmIsUp = 1;
  updateSensorValue(&swingArm);
  while(swingArm.val < SWING_ARM_MAX && !isTimedOut(t0 + 2000)){
  	updateSensorValue(&swingArm);
    moveSwingArm(UP);
    wait1Msec(10);
  }
  moveSwingArm(STOP);
}

void swingArmDown(){
	int t0 = time1[T1];
  moveSwingArm(DOWN);
	swingArmIsUp = 0;
	updateSensorValue(&swingArm);
  while(swingArm.val > SWING_ARM_MIN && !isTimedOut(t0 + 500)){
  	updateSensorValue(&swingArm);
    moveSwingArm(DOWN);
    wait1Msec(10);
  }
  moveSwingArm(STOP);
}

// ** Lift **
void moveLift(int status){
  if(status == UP){
    moveLift(127);
  }
  else if(status == DOWN){
    moveLift(-127);
  }
  else motorReq[M_LIFT] = status;

}

void moveLiftToCone(int coneNum){
	int liftVals[7] = {323, 640, 800, 909, 1118, 1267, 1333};
	liftVal = liftVals[coneNum];
	CONE_LIFT_COMMAND = PRESET;
}

task coneLiftTask(){

  pid liftPid;
  liftPid.kp = 0;
  liftPid.kd = 0;

  initializeSensor(&liftSensor, 1.0, I2C_1, &liftPid);

  int dbgCnt = 0;

  while(true){
  	updateSensorValue(&liftSensor);

    if(CONE_LIFT_COMMAND == HOLD){ //Keeps the lift at the same place
      #if DEBUG_CONE_LIFT == 1
        if(dbgCnt == 10){
          dbgCnt = 0;
        }
        else dbgCnt++;
      #endif
    }
    else if(CONE_LIFT_COMMAND == UP){
      moveLift(UP);
    }
    else if(CONE_LIFT_COMMAND == DOWN){
      moveLift(DOWN);
    }
    else if(CONE_LIFT_COMMAND == PRESET){
   		moveLift(SIGN(liftVal - liftSensor.val));
      if(abs(liftSensor.val - liftVal) < 5) CONE_LIFT_COMMAND = HOLD;
    }
    else if(CONE_LIFT_COMMAND == STOP){
      moveLift(STOP);
    }

    wait1Msec(10);
  }
}

#endif
