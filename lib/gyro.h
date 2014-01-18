#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     irLeft,         sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S3,     irRight,        sensorHiTechnicIRSeeker600)
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
