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

/* Copyright (c) 2013 AJ Stubberud. All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

//AUTONOMOUS FILE FROM 2013-2014

#include "JoystickDriver.c" // just for waitForStart()

#define DRIVE_SPEED 100
#define FORWARD_TIME 400
#define FORWARD_TIME_2 1250
#define TURN_TIME 2000

task main() {
	waitForStart();

	// Raise the arm
	motor[rotator] = 100;
	wait1Msec(2250);
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
	wait1Msec(2000);
	motor[leftTread] = 0;
	motor[rightTread] = 0;

	// Dumb turn onto the platform
	motor[rightDrive] = -DRIVE_SPEED;
	wait1Msec(TURN_TIME);
	motor[leftDrive] = -DRIVE_SPEED;
	motor[rightDrive] = -DRIVE_SPEED;
	wait1Msec(FORWARD_TIME_2);
}
