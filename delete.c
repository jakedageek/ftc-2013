#include "lib/event.h"

task main()
{
	Event ev;
	while(true) {
		Event_scan();
		Event_pop(&ev);

		if (ev.type != EVENT_TYPE_NONE) {
			writeDebugStreamLine("%d, %d, %d", ev.type, ev.controller, ev.data);
		}
	}
}
