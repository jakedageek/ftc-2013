#pragma config(Sensor, S1,     gyro,           sensorI2CHiTechnicGyro)

#define TIME_MAX 0xFFFF

bool initialized = false;
unsigned long lastUpdate = 0;

long getTimeDelta() {
	if (!initialized) {
		initialized = true;
		lastUpdate = nSysTime;
		return 0;
	}

	long delta;

	if (nSysTime < lastUpdate) {
		// The time has looped around
		delta = TIME_MAX - lastUpdate + nSysTime;
		lastUpdate = nSysTime;
	} else {
		delta = nSysTime - lastUpdate;
		lastUpdate = nSysTime;
	}

	return delta;
}

task main() {

	int zero = 0;
	float angle = 0;

	// Find the zero
	for (int i = 0; i < 9; i++) {
		zero += SensorValue[gyro];
		wait1Msec(100);
	}
	zero /= 10;

	while(true) {
		angle += ((SensorValue[gyro]) - zero) * getTimeDelta() / 1000.0;

		nxtDisplayTextLine(0, "%d", SensorValue[gyro]);
		nxtDisplayTextLine(1, "%.4f", angle);
		nxtDisplayTextLine(2, "%d", zero);
	}
}
