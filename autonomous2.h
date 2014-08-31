#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H
#define half_h 2
#define GyroScale 4 
#define t_scale 500 

void calibrateGyro();
void driveForward(int millis, int speed);
void driveForward(int speed);
void driveBackward(int millis, int speed);
void driveBackward(int speed);
void driveStop();
void turnRightEuler(int degrees, int speed);
void turnLeftEuler(int degrees, int speed);
int gyroValue();
int gyro_drift;

// This is the feedback loop gain 
float k1 = 0.2; // position feedback gain 
float k2 = 90; // velocity feedback gain 
float k3 = 8; // tilt feedback gain 
float k4 = 10.0; // angular velocity feedback gain 
long f1=0, f2=0; 
float GyroBias; 
theta_old = 0; 
t_old= nSysTime; 
f1=0; 
x_old=0; 

void calibrateGyro() {

	gyro_drift = 0;

	for (int i = 0; i < 10; i++) {
		gyro_drift += SensorValue[gyro];
		wait1Msec(100);
	}

	gyro_drift /= 10;
	writeDebugStreamLine("%d", gyro_drift);
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

void turnRightRK(int degrees, int speed) {
	float rotated = 0;
	int lastTime;

	motor[leftDrive] = speed;
	motor[rightDrive] = -speed;

	ClearTimer(T4);
	lastTime = time1[T4];

	while (abs(rotated) < degrees) {
		wait1Msec(half_h); 
		f2 = (SensorValue[gyro]-gyro_drift)/GyroScale; // f(tn) 
		wait1Msec(half_h);
		rotated = rotated + (f1+2*f2)*(nSysTime-t_old)/t_scale; 

	}

	driveStop();
}

void turnLeftEuler(int degrees, int speed) {
	float rotated = 0;
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

void turnLeftRK(int degrees, int speed) {
	float rotated = 0;

	motor[leftDrive] = -speed;
	motor[rightDrive] = speed;

	ClearTimer(T4);
	lastTime = time1[T4];

	while (abs(rotated) < degrees) {
		wait1Msec(half_h); 
		f2 = (SensorValue[gyro]-gyro_drift)/GyroScale; // f(tn) 
		wait1Msec(half_h);
		rotated = rotated + (f1+2*f2)*(nSysTime-t_old)/t_scale; 

	}

	driveStop();
}

int gyroValue() {
	return SensorValue[gyro] - gyro_drift;
}

#endif
