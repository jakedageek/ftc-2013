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
