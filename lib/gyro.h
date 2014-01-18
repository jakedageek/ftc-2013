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
