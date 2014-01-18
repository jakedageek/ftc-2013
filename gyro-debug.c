#pragma config(Sensor, S1,     gyro,           sensorI2CHiTechnicGyro)

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
