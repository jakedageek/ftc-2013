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

#ifndef TIMING_H
#define TIMING_H

#define TIME_MAX 0xFFFF

bool timing_initialized = false;
bool timing_timer_initialized = false;
unsigned long timing_lastUpdate = 0;
unsigned long timing_timer_lastValue = 0;
TTimers timing_timer = T4;

unsigned long getTimeDelta() {
	if (!timing_initialized) {
		timing_initialized = true;
		timing_lastUpdate = nSysTime;
		return 0;
	}

	// ############# Bug #1 ###############
	// It seems that the system clock is not updated
	// without this wait call.  It is required to get
	// the scheduler to run the OS code properly
	wait1Msec(1);

	long delta;

	if (nSysTime < timing_lastUpdate) {
		// The time has looped around
		delta = TIME_MAX - timing_lastUpdate + nSysTime;
		timing_lastUpdate = nSysTime;
	} else {
		delta = nSysTime - timing_lastUpdate;
		timing_lastUpdate = nSysTime;
	}

	return delta;
}

void resetTimeDelta() {
	timing_initialized = false;
}

void setTimeDeltaTimer(TTimers timer) {
	timing_timer_initialized = false;
	timing_timer = timer;
}

void resetTimeDeltaTimer() {
	timing_timer_initialized = false;
}

unsigned long getTimeDeltaTimer() {
	if (!timing_timer_initialized) {
		ClearTimer(timing_timer);
		timing_timer_initialized = true;
		timing_timer_lastValue = 0;
	}

	long time = time1[timing_timer];
	long delta = time - timing_timer_lastValue;
	timing_timer_lastValue = time;

	return delta;
}

#endif // TIMING_H
