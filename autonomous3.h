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
int degreeOffset(int degrees, int speed);

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
	float lastTime;

	motor[leftDrive] = speed;
	motor[rightDrive] = -speed;

	lastTime = nSysTime;

	while (abs(rotated) < degrees) {
		float g_val = gyroValue();
		float dt = nSysTime - lastTime;
		lastTime = nSysTime;
		rotated += (dt/1000.) * g_val;
		writeDebugStreamLine("rotated %f", rotated);
		writeDebugStreamLine("time %f", dt);
		writeDebugStreamLine("gval %f", g_val);
		wait1Msec(4);
	}
	writeDebugStreamLine("-----------------------");
	driveStop();
}

void turnLeftEuler(int degrees, int speed) {
	float rotated = 0;
	float lastTime;
	int i;

	motor[leftDrive] = -speed;
	motor[rightDrive] = speed;

	lastTime = nSysTime;

	while (abs(rotated) < degrees) {
		float g_val = gyroValue();
		float dt = nSysTime - lastTime;
		lastTime = nSysTime;
		rotated += (dt/1000.) * g_val;
		writeDebugStreamLine("rotated %f", rotated);
		writeDebugStreamLine("time %f", dt);
		writeDebugStreamLine("gval %f", g_val);
		wait1Msec(4);
	}
	writeDebugStreamLine("-----------------------");
	driveStop();
	for(i = 0; i < 100; i++){
		float g_val = gyroValue();
		float dt = nSysTime - lastTime;
		lastTime = nSysTime;
		rotated += (dt/1000.) * g_val;
		writeDebugStreamLine("rotated %f", rotated);
		writeDebugStreamLine("time %f", dt);
		writeDebugStreamLine("gval %f", g_val);
		wait1Msec(4);
	}
}

int gyroValue() {
	return SensorValue[gyro] - gyro_zero;
}

int degreeOffset(int degrees, int speed){
	degrees -= 5 * ((degrees-20) / 10 );
	return degrees;
}

#endif
