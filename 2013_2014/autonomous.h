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

//This code has been kept for reference - autonomous3.h is updated.



#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

void calibrateGyro();
void driveForward(int millis, int speed);
void driveForward(int speed);
void driveBackward(int millis, int speed);
void driveBackward(int speed);
void driveStop();
void turnRightEuler(int degrees, int speed);
void turnLeftEuler(int degrees, int speed);
int gyroValue();

int gyro_zero;

void calibrateGyro() {
	gyro_zero = 0;

	for (int i = 0; i < 10; i++) {
		gyro_zero += SensorValue[gyro];
		wait1Msec(100);
	}

	gyro_zero /= 10;
	writeDebugStreamLine("%d", gyro_zero);
}

void driveForward(int millis, int speed) {
	driveForward(speed);
	wait1Msec(millis);
	driveStop();
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

void driveStop() {
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}

void turnRightEuler(int degrees, int speed) {
	float rotated = 0;
	int lastTime;

	motor[leftDrive] = speed;
	motor[rightDrive] = -speed;

	ClearTimer(T4);
	lastTime = time1[T4];

	while (abs(rotated) < degrees) {
		int g_val = gyroValue();
		int dt = time1[T4] - lastTime;
		lastTime = time1[T4];

		rotated += (float) dt / 1000.0 * (float) g_val;
	}

	driveStop();
}

void turnLeftEuler(int degrees, int speed) {
	float rotated = 0;
	int lastTime;

	motor[leftDrive] = -speed;
	motor[rightDrive] = speed;

	ClearTimer(T4);
	lastTime = time1[T4];

	while (abs(rotated) < degrees) {
		int g_val = gyroValue();
		int dt = time1[T4] - lastTime;
		lastTime = time1[T4];

		rotated += (float) dt / 1000.0 * (float) g_val;
	}

	driveStop();
}

int gyroValue() {
	return SensorValue[gyro] - gyro_zero;
}

#endif
