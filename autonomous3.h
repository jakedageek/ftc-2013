#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

void calibrateGyro();
void driveForward(int millis, int speed);
void driveForward(int speed);
void driveBackward(int millis, int speed);
void driveBackward(int speed);
void driveForwardDist(int inches, int speed);
void driveBackwardDist(int inches, int speed);
void driveStop(bool forward);
void turnEuler(int degrees, int speed, bool left);
int gyroValue();
int gyro_zero;

#include "util.h"


/*
Copyright (c) 2014 Jake Lee, AJ Stubbard, Team 4790

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


//gyroscope calibration - run before use
void calibrateGyro() {
	gyro_zero = 0;

	for (int i = 0; i < 10; i++) {
		gyro_zero += SensorValue[gyro];
		wait1Msec(100);
	}

	gyro_zero /= 10;
	writeDebugStreamLine("%d", gyro_zero);
}

//self-explanatory - for use in autonomous
void driveForward(int millis, int speed) {
	driveForward(speed);
	wait1Msec(millis);
	driveStop(true);
}

void driveForward(int speed) {
	motor[leftDrive] = speed;
	motor[rightDrive] = speed;
}

void driveBackward(int millis, int speed) {
	driveForward(millis, -speed);
}

void driveBackward(int speed) {
	driveForward(-speed);
}

void driveForwardDist(int inches, int speed) {
	//driving forward using the angle sensor
	int degrees;
	int initAng;
	initAng = HTANGreadAccumulatedAngle(HTANG);		//reset accumulated angle
	wait1Msec(100);
	degrees = (inches - 1) * 80;		//momentum drives forward by 1 inch at 20 speed [M]
	while(abs(HTANGreadAccumulatedAngle(HTANG)-initAng) < degrees){
		motor[leftDrive] = speed;
		motor[rightDrive] = speed;
		writeDebugStreamLine("accumulated angle = %d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
	}
	writeDebugStreamLine("------------------------");
	driveStop(true);
	wait1Msec(100);
	writeDebugStreamLine("%d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
}

void driveBackwardDist(int inches, int speed) {
	//driving backward using the angle sensor
	int degrees;
	int initAng;
	initAng = HTANGreadAccumulatedAngle(HTANG);		//reset accumulated angle
	wait1Msec(100);
	degrees = (inches - 1) * 80;		//momentum drives forward by 1 inch at 20 speed [M]
	while(abs(HTANGreadAccumulatedAngle(HTANG)-initAng) < degrees){
		motor[leftDrive] = -speed;
		motor[rightDrive] = -speed;
		writeDebugStreamLine("accumulated angle: %d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
	}
	writeDebugStreamLine("------------------------");
	driveStop(false);
	wait1Msec(100);
	writeDebugStreamLine("%d",abs(HTANGreadAccumulatedAngle(HTANG)-initAng));
}

void driveStop(bool forward) {
	//braking is a lot quicker when something is sent to the motors
	if(forward == true){
		motor[leftDrive] = -1;
		motor[rightDrive] = -1;
		wait1Msec(50);
		motor[leftDrive] = 0;
		motor[rightDrive] = 0;
	}else{
		motor[rightDrive] = 1;
		motor[leftDrive] = 1;
		wait1Msec(50);
		motor[leftDrive] = 0;
		motor[rightDrive] = 0;
	}
}

//Gyroscope turn function
void turnEuler(int degrees, int speed, bool left) { // degrees in degrees, speed in %, left (true), right (false)
	float lastTime = 0;				//used for dt calculation
	float dt = 0;					//dt for integration
	float g_val = 0;				//gyro value in degrees per second
	float currPos = 0;				//current turn position
	float downPos = 0;				//decceleration point
	float halfdeg = 0;				//half of angle target
	int maxSpeed = speed;			//maximum speed
	int minSpeed = 25;				//minimum speed
	float currSpeed = 0;			//current speed
	float accelVal = 0;				//acceleration in power/10Msec
	float slopeTime = 600; 			// time to accel in Msec
	int i;							//counters

	//define halfdeg for cutting of acceleration
	halfdeg = degrees /2 ;
	writeDebugStreamLine("halfdeg = %d", halfdeg);

	//get the motors moving
	if(left){
		motor[leftDrive] = (int) -minSpeed;
		motor[rightDrive] = (int) minSpeed;
	}else{
		motor[leftDrive] = (int) minSpeed;
		motor[rightDrive] = (int) -minSpeed;
	}
	currSpeed = minSpeed;

	//define acceleration rate
	accelVal = ((maxSpeed - minSpeed) / slopeTime) * 10;
	writeDebugStreamLine("accelVal = %f", accelVal);

	//acceleration
	writeDebugStreamLine("accelerating!");
	lastTime = nSysTime;
	for(i=0; i < (slopeTime/10); i++){
		//integration start
		g_val = gyroValue();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		//integration end
		writeDebugStreamLine("rotated %f", currPos);
		if(currPos >= halfdeg){		//if the acceleration is going past half of the total angle, break and go into decceleration
			writeDebugStreamLine("breaking from accel!");
			break;
		}
		currSpeed += accelVal;		//increment every time by acceleration value
		writeDebugStreamLine("current speed = %f", currSpeed);
		if(left){
			motor[leftDrive] = (int) -currSpeed;
			motor[rightDrive] = (int) currSpeed;
		}else{
			motor[leftDrive] = (int) currSpeed;
			motor[rightDrive] = (int)-currSpeed;
		}

		wait1Msec(10 - dt);		//always 10 Msec delay, despite changes in dt
	}

	//calculate when it needs to setart deccelerating
	downPos = degrees - (30);
	writeDebugStreamLine("downPos = %d", downPos);

	//constant max speed
	if(left){
		motor[leftDrive] = (int) -maxSpeed;
		motor[rightDrive] = (int) maxSpeed;
	}else{
		motor[leftDrive] = (int) maxSpeed;
		motor[rightDrive] = (int) -maxSpeed;
	}

	//keep integrating until we reach downPos
	lastTime = nSysTime;
	while(true){
		//integration start
		g_val = gyroValue();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		//integration end
		if(currPos >= downPos){
			break;
		}
		wait1Msec(10 - dt);
	}

	writeDebugStreamLine("deccelerating!");
	//decceleration
	lastTime = nSysTime;
	for(i=0; i < (slopeTime/10); i++){
		//integration start
		g_val = gyroValue();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		//integration end
		writeDebugStreamLine("rotated %f", currPos);
		currSpeed -= (accelVal * 3.5);		//increment every time by acceleration value
		writeDebugStreamLine("currSpeed %f", currSpeed);

		//if speed is incremented below the minimum speed, reset to min speed
		if(currSpeed < minSpeed){
			currSpeed = minSpeed;
		}

		//if position goes past the target, stop
		if(currPos >= (degrees - (maxSpeed/20))){
			writeDebugStreamLine("stopping!");
			//turn the motors the opposite direction to prevent coasting
			if(left){
				motor[leftDrive] = 5;
				motor[rightDrive] = -5;
			}else{
				motor[leftDrive] = -5;
				motor[rightDrive] = 5;
			}
			wait1Msec(10);
			motor[leftDrive] = 0;
			motor[rightDrive] = 0;
			break;
		}

		if(left){
			motor[leftDrive] = (int) -currSpeed;
			motor[rightDrive] = (int) currSpeed;
		}else{
			motor[leftDrive] = (int) currSpeed;
			motor[rightDrive] = (int) -currSpeed;
		}

		if(i == (slopeTime/10)-1 && currPos < degrees)
			i -= 1;

		wait1Msec(10 - dt);		//always 10 Msec delay
	}

	//debug code to measure overturns
	writeDebugStreamLine("Overturning:");
	lastTime = nSysTime;
	for(i=0; i < 30; i++) {
		g_val = gyroValue();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		writeDebugStreamLine("rotated %f", currPos);
		wait1Msec(10 - dt);
	}
	writeDebugStreamLine("done.");
	writeDebugStreamLine("----------------------------");
}

int gyroValue() {
	return abs(SensorValue[gyro] - gyro_zero);
}



#endif
