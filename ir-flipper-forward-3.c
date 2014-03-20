#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irBack,         sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S3,     irFront,        sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     leftDrive,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightDrive,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     rotator,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     leftTread,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     rightTread,    tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    flipper,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    blockLoader,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    flagExtender,         tServoStandard)

#define DRIVE_SPEED 50
#define SEARCH_TIME 1500
#define FIRST_HALF_DELAY 300
#define SECOND_HALF_DELAY 200
#define MIDDLE_TIME 1000
#define TURN_90_EULER 70

#include "JoystickDriver.c"
#include "autonomous.h"
#include "flipper.h"
#include "block-loader.h"

task main() {
	calibrateGyro();

	{ // Drive to the IR basket, dump the block, drive back & square up against the wall
		int timeForward;

		ClearTimer(T1);
		driveForward(DRIVE_SPEED);
		while (true) {
			if (time1[T1] > SEARCH_TIME)
				break;
			else if (SensorValue[irFront] == 8)
				break;
		}

		timeForward = time1[T1];

		// Keep moving to adjust for the first 2 / last 2 baskets
		if (timeForward > MIDDLE_TIME)
			wait1Msec(SECOND_HALF_DELAY);
		else
			wait1Msec(FIRST_HALF_DELAY);
		timeForward = time1[T1];

		driveStop();
		servo[blockLoader] = BLOCK_LOADER_IN;
		flipper_flip();
		driveBackward(timeForward + 2000, DRIVE_SPEED);
	}

	{ // Drive next to the ramp & turn on to it
		motor[leftDrive] = DRIVE_SPEED;
		wait1Msec(950);
		motor[rightDrive] = DRIVE_SPEED;
		wait1Msec(1000);
		driveStop();
		wait1Msec(500);
		turnRightEuler(TURN_90_EULER, DRIVE_SPEED);
		PlaySound(soundBeepBeep);
		driveBackward(1500, DRIVE_SPEED);
	}
}
