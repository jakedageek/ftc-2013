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
#define FIRST_HALF_DELAY 200
#define SECOND_HALF_DELAY 300
#define MIDDLE_TIME 1000
#define TURN_90_EULER 75

#include "JoystickDriver.c"
#include "autonomous.h"
#include "flipper.h"
#include "block-loader.h"

task main() {
	waitForStart();
	calibrateGyro();

	{ // Drive to the IR basket, dump the block, drive back & square up against the wall
		int timeForward;

		ClearTimer(T1);
		driveBackward(DRIVE_SPEED);
		while (true) {
			if (time1[T1] > SEARCH_TIME) {
				writeDebugStreamLine("Ran out of time, just dump the block");
				break;
			} else if (SensorValue[irBack] == 2)
				break;
		}

		timeForward = time1[T1];
		writeDebugStreamLine("ir-flipper-backward-3: Sensor value: %d", SensorValue[irBack]);
		PlaySound(soundBeepBeep);

		// Keep moving to adjust for the first 2 / last 2 baskets
		if (timeForward < MIDDLE_TIME) {
			// Back up a little
			driveStop();
			wait1Msec(500);
			driveForward(FIRST_HALF_DELAY, DRIVE_SPEED);
			timeForward -= FIRST_HALF_DELAY;
		} else {
			// Back up a little
			driveStop();
			wait1Msec(500);
			driveForward(SECOND_HALF_DELAY, DRIVE_SPEED);
			timeForward -= SECOND_HALF_DELAY;
		}

		driveStop();
		flipper_flip();
		driveForward(timeForward + 1500, DRIVE_SPEED);
		motor[leftDrive] = -10;
		motor[rightDrive] = DRIVE_SPEED;
		wait1Msec(500);
		driveStop();
	}

	{ // Drive next to the ramp & turn on to it
		motor[leftDrive] = -DRIVE_SPEED;
		wait1Msec(1150);
		motor[rightDrive] = -DRIVE_SPEED;
		wait1Msec(1100);
		driveStop();
		turnRightEuler(TURN_90_EULER, DRIVE_SPEED);
		PlaySound(soundBeepBeep);
		driveBackward(1500, DRIVE_SPEED);
	}
}
