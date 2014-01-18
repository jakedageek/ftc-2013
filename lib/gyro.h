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

#ifndef GYRO_H
#define GYRO_H

#include "lib/timing.h"

void calibrateGyro();
void turnRight(float degrees, int speed);
void turnLeft(float degrees, int speed);

int gyro_zero;

void calibrateGyro() {
	gyro_zero = 0;

	for (int i = 0; i < 9; i++) {
		gyro_zero += SensorValue[gyro];
		wait1Msec(100);
	}
	gyro_zero /= 10;
}

void turnRight(float degrees, int speed) {
	float turned = 0;

	wait1Msec(1000);
	resetTimeDelta();
	getTimeDelta();
	motor[leftDrive] = speed;
	motor[rightDrive] = -speed;

	while(abs(turned) < degrees) {
		turned += (SensorValue[gyro] - gyro_zero) * getTimeDelta() / 1000.0;
	}

	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}

void turnLeft(float degrees, int speed) {
	float turned = 0;

	wait1Msec(1000);
	resetTimeDelta();
	getTimeDelta();
	motor[leftDrive] = -speed;
	motor[rightDrive] = speed;

	while(abs(turned) < degrees) {
		turned += (SensorValue[gyro] - gyro_zero) * getTimeDelta() / 1000.0;
	}

	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}

#endif // GYRO_H
