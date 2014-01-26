#include "lib/timing.h"

task main()
{
	writeDebugStreamLine("Waiting 1 second");
	resetTimeDelta();
	getTimeDelta();
	wait1Msec(1000);
	writeDebugStreamLine("delta: %d", getTimeDelta());

	writeDebugStreamLine("Waiting 5 seconds");
	resetTimeDelta();
	getTimeDelta();
	wait1Msec(5000);
	writeDebugStreamLine("delta: %d", getTimeDelta());

	writeDebugStreamLine("Waiting 10 seconds");
	resetTimeDelta();
	getTimeDelta();
	wait1Msec(10000);
	writeDebugStreamLine("delta: %d", getTimeDelta());
}
