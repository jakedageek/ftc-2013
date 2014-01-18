#ifndef TIMING_H
#define TIMING_H

#define TIME_MAX 0xFFFF

bool timing_initialized = false;
unsigned long timing_lastUpdate = 0;

long getTimeDelta() {
	if (!timing_initialized) {
		timing_initialized = true;
		timing_lastUpdate = nSysTime;
		return 0;
	}

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

#endif // TIMING_H
