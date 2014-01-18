#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     irLeft,         sensorI2CCustom)
#pragma config(Sensor, S3,     irRight,        sensorI2CCustom)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     rotator,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     leftTread,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     rightTread,    tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    extender,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    flagExtender,         tServoStandard)

#include "lib/event.h" // I have no idea where waitForStart() is declared

#define DRIVE_SPEED 100
#define FORWARD_TIME 500
#define FORWARD_TIME_2 2000
#define TURN_TIME 2000

task main() {
	//waitForStart();

	// Raise the arm
	motor[rotator] = 100;
	wait1Msec(2750);
	motor[rotator] = 0;

	// Drive forward
	motor[leftDrive] = DRIVE_SPEED;
	motor[rightDrive] = DRIVE_SPEED;
	wait1Msec(FORWARD_TIME);
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;

	// Eject the block
	motor[leftTread] = -60;
	motor[rightTread] = -60;
	wait1Msec(3000);
	motor[leftTread] = 0;
	motor[rightTread] = 0;

	// Dumb turn onto the platform
	motor[leftDrive] = -DRIVE_SPEED;
	wait1Msec(TURN_TIME);
	motor[leftDrive] = -DRIVE_SPEED;
	motor[rightDrive] = -DRIVE_SPEED;
	wait1Msec(FORWARD_TIME_2);
}
