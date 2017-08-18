#ifndef CONFIG_C
#define CONFIG_C


//Configure preauton
void preAutonProcedure(){
  //This code runs during preauton
}

void userControlProcedure(){
  //This code executes inside the user control while loop
}


//Set up push release buttons
#define USE_PR_BUTTON  1
#define NUM_PR_BUTTONS  3 //Only include if using remote

#define Btn8U_Partner 0
#define Btn8D_Partner 1
#define Btn8L_Partner 2

void setUpButtons(){ //Only include if using remote
  addPrButton(Btn8U_Partner, Btn8U);
  addPrButton(Btn8D_Partner, Btn8D);
  addPrButton(Btn8L_Partner, Btn8L);
}

//Configure Sensors
#define USE_SECOND_BATTERY 1

#define USE_LCD 1

void lcdGenerateMessage(){
  sprintf(lcdStr1, "8900 %4.1fV %4.1fV", getMainBatteryVoltage() / 1000.0, getSecondBatteryVoltage() / 1000.0);
  sprintf(lcdStr2, "%3d %3d %d", motor[M_FIRST_LIFT2], motor[M_SECOND_LIFT], coneNum);
}

/*
  MOTOR CONTROL
*/

//Slew Rate
#define USE_SLEW  1 //Disable if slew interferes with move functions or slows robot down
int MOTOR_SLEW[MOTOR_NUM] = {255, 40, 40, 255, 255, 255, 255, 40, 40, 255};

#define USE_MOVE 0

/*
  DEBUGGING TOGGLES
*/

#define DEBUG_SLEW  0

#define BAILOUT_BUTTON Btn7D
void bailOut(){
	CONE_LIFT_COMMAND = STOP;
  clawIsClosed = 0;
  clawIsOpened = 0;
}

void move(int V, int H, int X){
  motorReq[M_WHEEL_L1] = BOUND(V + H, -127, 127);
  motorReq[M_WHEEL_L2] = BOUND(V + H, -127, 127);
  motorReq[M_WHEEL_R1] = BOUND(V - H, -127, 127);
  motorReq[M_WHEEL_R2] = BOUND(V - H, -127, 127);
}


#endif
