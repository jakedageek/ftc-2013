#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

void calibrateGyro();
void driveForward(int millis, int speed);
void driveForward(int speed);
void driveBackward(int millis, int speed);
void driveBackward(int speed);
void driveStop();
void turnEuler(int degrees, int speed, bool left);
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

void turnEuler(int degrees, int speed, bool left) {
	float lastTime = 0;				//used for dt calculation
	float dt = 0;							//dt for integration
	float g_val = 0;					//gyro value in degrees per second
	float currPos = 0;		//current turn position
	float downPos = 0;				//decceleration point
	float halfdeg = 0;				//half of angle target
	int maxSpeed = speed;	//maximum speed
	int minSpeed = 16;	//minimum speed
	float currSpeed = 0;			//current speed
	float accelVal = 0;			//acceleration in power/10Msec
	float slopeTime = 600; // time to accel in Msec
	int i;						//counters

	//define halfdeg
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

	//define acceleration
	accelVal = ((maxSpeed - minSpeed) / slopeTime) * 10;
	writeDebugStreamLine("accelVal = %f", accelVal);

	//acceleration
	writeDebugStreamLine("accelerating!");
	lastTime = nSysTime;
	for(i=0; i < (slopeTime/10); i++){
		g_val = gyroValue();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		writeDebugStreamLine("rotated %f", currPos);
		if(currPos >= halfdeg){		//if the acceleration is going past half of the total angle
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

		wait1Msec(10 - dt);		//always 10 Msec delay
	}
	//calculate when it needs to setart deccelerating
	downPos = degrees - (30);
	writeDebugStreamLine("downPos = %d", downPos);

	//constant speed
	if(left){
		motor[leftDrive] = (int) -maxSpeed;
		motor[rightDrive] = (int) maxSpeed;
	}else{
		motor[leftDrive] = (int) maxSpeed;
		motor[rightDrive] = (int) -maxSpeed;
	}

	lastTime = nSysTime;
	while(true){
		g_val = gyroValue();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		if(currPos >= downPos){
			break;
		}
		wait1Msec(10 - dt);
	}
	writeDebugStreamLine("deccelerating!");
	//decceleration
	lastTime = nSysTime;
	for(i=0; i < (slopeTime/10); i++){
		g_val = gyroValue();
		dt = nSysTime - lastTime;
		lastTime = nSysTime;
		currPos += (dt/1000.) * g_val;
		writeDebugStreamLine("rotated %f", currPos);
		currSpeed -= (accelVal * 3.5);		//increment every time by acceleration value
		writeDebugStreamLine("currSpeed %f", currSpeed);

		//if speed is incremented below the minimum speed
		if(currSpeed < minSpeed){
			currSpeed = minSpeed;
		}

		//if position goes past the speed target
		if(currPos >= (degrees-5)){
			writeDebugStreamLine("stopping!");
			if(left){
				motor[leftDrive] = 5;
				motor[rightDrive] = -5;
			}else{
				motor[leftDrive] = -5;
				motor[rightDrive] = 5;
			}
			wait1Msec(10);
			driveStop();
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

int degreeOffset(int degrees, int speed){
	degrees -= 5 * ((degrees-20) / 10 );
	return degrees;
}

#endif
