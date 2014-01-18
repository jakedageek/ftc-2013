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

#ifndef EVENT_H
#define EVENT_H

#include "JoystickDriver.c"
#include "util.h"

#define EVENT_TYPE_NONE 0x00
#define EVENT_TYPE_BUTTON_DOWN 0x01
#define EVENT_TYPE_BUTTON_UP 0x02
#define EVENT_TYPE_DPAD 0x03

#define EVENT_CONTROLLER_NONE 0x00
#define EVENT_CONTROLLER_1 0x10
#define EVENT_CONTROLLER_2 0x11

#define MAX_EVENTS 200
#define NUM_BUTTONS 13

typedef struct {
	int type;
	int controller;
	int data;
} Event;

// Functions
void Event_scan();
void Event_push(Event *ev);
void Event_pop(Event *ret);
int Event_nextIndex(int i);

// Variables
Event Event_array[MAX_EVENTS];
int Event_front = 0;
int Event_back = 0;
int Event_filled = 0;
short Event_buttonState1 = 0x00;
short Event_buttonState2 = 0x00;
short Event_dpadState1 = 0x00;
short Event_dpadState2 = 0x00;

void Event_scan() {
	getJoystickSettings(joystick);

	// Button events
	{
		// Controller 1
		for (int i = 0; i < NUM_BUTTONS; i++) {
			short mask = 1 << i;
			bool state = (Event_buttonState1 & mask);
			bool now = (joystick.joy1_Buttons & mask);
			if (state != now) {
				Event ev;
				ev.controller = EVENT_CONTROLLER_1;
				if (now) {
					ev.type = EVENT_TYPE_BUTTON_DOWN;
					Event_buttonState1 |= mask;
				} else {
					ev.type = EVENT_TYPE_BUTTON_UP;
					Event_buttonState1 &= ~mask;
				}
				Event_push(&ev);
			}
		}

		// Controller 2
		for (int i = 0; i < NUM_BUTTONS; i++) {
			short mask = 1 << i;
			bool state = (Event_buttonState2 & mask);
			bool now = (joystick.joy2_Buttons & mask);
			if (state != now) {
				Event ev;
				ev.controller = EVENT_CONTROLLER_2;
				if (now) {
					ev.type = EVENT_TYPE_BUTTON_DOWN;
					Event_buttonState2 |= mask;
				} else {
					ev.type = EVENT_TYPE_BUTTON_UP;
					Event_buttonState2 &= ~mask;
				}
				Event_push(&ev);
			}
		}
	}

	// D-PAD events
	{
		// Controller 1
		short c1dpad = joystick.joy1_TopHat;
		if (c1dpad != Event_dpadState1) {
			// new event
			Event ev;
			ev.type = EVENT_TYPE_DPAD;
			ev.controller = EVENT_CONTROLLER_1;
			ev.data = c1dpad;
			Event_push(&ev);
			// update the state
			Event_dpadState1 = c1dpad;
		}

		// Controller 2
		short c2dpad = joystick.joy2_TopHat;
		if (c2dpad != Event_dpadState2) {
			// new event
			Event ev;
			ev.type = EVENT_TYPE_DPAD;
			ev.controller = EVENT_CONTROLLER_2;
			ev.data = c1dpad;
			Event_push(&ev);
			// update the state
			Event_dpadState2 = c1dpad;
		}
	}
}

void Event_push(Event *ev) {
	int i = Event_nextIndex(Event_back);

	// Check to see if there is room in the queue
	if (Event_filled == MAX_EVENTS) {
		writeDebugStreamLine("There is no room in the event queue");
		return;
	}

	Event_array[Event_back].type = ev->type;
	Event_array[Event_back].controller = ev->controller;
	Event_array[Event_back].data = ev->data;
	Event_back = i;
	Event_filled++;
}

void Event_pop(Event *ret) {
	int i = Event_nextIndex(Event_front);

	// Check to see if the queue is empty
	if (Event_filled == 0) {
		//writeDebugStreamLine("Queue is empty");
		ret->type = EVENT_TYPE_NONE;
		ret->controller = EVENT_CONTROLLER_NONE;
		ret->data = 0;
		return;
	}

	// Return the event
	ret->type = Event_array[Event_front].type;
	ret->controller = Event_array[Event_front].controller;
	ret->data = Event_array[Event_front].data;
	// Clear it
	Event_array[Event_front].type = EVENT_TYPE_NONE;
	Event_array[Event_front].controller = EVENT_CONTROLLER_NONE;
	Event_array[Event_front].data = 0;
	Event_front = i;
	Event_filled--;
}

int Event_nextIndex(int i) {
	i++;
	if (i >= MAX_EVENTS) {
		i = 0;
	}
	return i;
}

#endif // EVENT_H
