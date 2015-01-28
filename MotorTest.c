#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C2_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     liftLeft,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     liftRight,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    bananaServo,          tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    gateBack,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    hookRight,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    hookLeft,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)

#include "util.h"
#include "lift.h"
#include "autonomous3.h"

task main()
{
	hook(true);
	banana(false);
	gate(false);

	wait1Msec(2000);
	while(true){
	      if(joystick.joy1_TopHat == 6){
					//ball carrier up
  				banana(true);
  				writeDebugStreamLine("Banana true");
				}else if(joystick.joy1_TopHat == 4){
					//ball carrier down
					banana(false);
					writeDebugStreamLine("Banana false");
				}else{
					writeDebugStreamLine("else statement");
				}

				if(joy1Btn(CONTROLLER_A)){
					liftMove(SIXTY_LIFT);
				}else if(joy1Btn(CONTROLLER_B)){
					liftMove(NINETY_LIFT);
				}else if(joy1Btn(CONTROLLER_Y)){
					liftMove(GOAL_LIFT);
				}else if(joy1Btn(CONTROLLER_X)){
					liftMove(RESET);
				}else if(joy1Btn(CONTROLLER_R1)){ //manual adjustment in case encoder or lift goes wack
		        liftMan(0);
		    }else if(joy1Btn(CONTROLLER_R2)){
		        liftMan(1);
		    }else{
		    		liftMan(2);
		  	}

				if(joystick.joy1_TopHat == 2){
					//ball release
					gate(true);
				}else{
					//ball close
					gate(false);
				}

				if(joy1Btn(CONTROLLER_BK)){
					bananaKnock();
				}

				motor[leftDrive] = scaleJoystick(joystickValue(1, 1, 2));
        motor[rightDrive] = scaleJoystick(joystickValue(1, 2, 2));
			}
}
