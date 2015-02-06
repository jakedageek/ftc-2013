#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C2_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     liftLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     inLeft,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     inRight,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     liftRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C1_1,    bananaServo,          tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    gateBack,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    hookFront,            tServoStandard)
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

const tMUXSensor HTANG = msensor_S3_1;
const tMUXSensor Sonar = msensor_S3_2;

//RAMP AUTONOMOUS

void initializeRobot(){
	calibrateGyro();
	nMotorEncoder[liftLeft] = 0;		//reset encoder
	hook(true);			//reset servos
	banana(false);
	gate(false);
	servo[hookFront] = 207;
	//RESET SERVOS
	return;
}

task main()
{
	initializeRobot();		//reset servos

	waitForStart();

	/* LIFT LIFT BEFORE MOVING OFF PARKZONE */
	liftMan(0);
	wait1Msec(200);
	liftMan(2);

	driveBackwardDist(20, 40);

	turnEuler(33, 50, false);

	driveBackwardDistAC(42, 70);

	wait1Msec(200);

	turnEuler(32, 50, true);

	driveBackwardDistAC(34, 70);

	driveBackwardDist(18, 20);

	hook(false);
	liftMove(THIRTY_LIFT);
	wait1Msec(1000);
	gate(true);
	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);
	liftMove(500);

	turnEuler(110, 60, true);

	driveForwardDist(10, 30);

	servo[hookFront] = 56;

	wait1Msec(700);

	driveBackwardDist(10, 30);

	turnEuler(120, 60, false);

	driveForwardDistAC(90, 100);

	turnEuler(65, 60, false);

	driveForwardDist(10,30);

}
