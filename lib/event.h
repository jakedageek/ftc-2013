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

// This header file houses an event-based input engine
// which allows you to detect button presses and D-PAD
// changes, rather than query which buttons are being held
// at a given monment.
//
// Here are the functions you should be aware of:
// - task EventThread()
// - void consumeEvent(Event *returnValue)
//
// Here are the data structures you should be aware of:
// - Event (struct):
//   - EventType type
//   - EventData data
//
// Here are the data types you should be aware of:
// - EventType - enumeration to differentiate between types
//   of events.  There are several different types:
//   - EVENT_TYPE_NONE
//   - EVENT_TYPE_CONTROLLER_1_BUTTON_DOWN
//   - EVENT_TYPE_CONTROLLER_1_BUTTON_UP
//   - EVENT_TYPE_CONTROLLER_1_POV_CHANGE (changes in state of D-PAD)
//   - EVENT_TYPE_CONTROLLER_2_BUTTON_DOWN
//   - EVENT_TYPE_CONTROLLER_2_BUTTON_UP
//   - EVENT_TYPE_CONTROLLER_2_POV_CHANGE
// - EventData - just declared as `typedef int'
//
// To start the engine, just launch the EventThread task
// when your program runs, like so:
//     StartTask(EventThread)
//
// The event thread will detect events and add them to the
// queue automatically.  When you want the engine to tell you
// what it has detected, call consumeEvent() like this:
//     Event detectedEvent;
//     consumeEvent(&detectedEvent);
//
// consumeEvent() will return the first event on the queue;
// this event could be empty or filled.  After you ask the
// engine for the event, you can check to see what type of
// event you have by looking at the values of
// detectedEvent.type and detectedEvent.data.  The 'type' field
// tells you what type of event it is.  The 'data' field
// is just a number associated with the event.  For button press
// events, the number will be equivalent to the number of the
// button being pressed or released (you can view the codes in
// util.h)
//
// Additional notes:
// Don't go too long without checking to see if the event engine
// has detected anything.  Each button press generates an event,
// and the queue has a maximum size of 200.  Events in excess of
// this will be dropped.

#ifndef EVENT_H
#define EVENT_H

/*
 *           event array
 * _______________________________
 * |    |    |    |    |    |    |
 * |    |    |    |    |    |    |
 * -------------------------------
 *         ^
 *         |
 *       cursor
 *
 * consumeEvent()
 *     - return the event under the cursor
 *     - zero out the event under the cursor
 *     - increment the cursor
 */

#include "util.h"
#include "thread.h"
#include "JoystickDriver.c"

#define MAX_EVENTS 200
#define NUM_BUTTONS 13
#define eventIsEmpty(x) (x->type == EVENT_TYPE_NONE)

typedef int EventData;

typedef enum {
    EVENT_TYPE_NONE,
    EVENT_TYPE_CONTROLLER_1_BUTTON_DOWN,
    EVENT_TYPE_CONTROLLER_1_BUTTON_UP,
    EVENT_TYPE_CONTROLLER_1_POV_CHANGE,
    EVENT_TYPE_CONTROLLER_2_BUTTON_DOWN,
    EVENT_TYPE_CONTROLLER_2_BUTTON_UP,
    EVENT_TYPE_CONTROLLER_2_POV_CHANGE
} EventType;

typedef struct {
    EventType type;
    EventData data;
} Event;

// -------------------------
// Global variable declarations

Mutex _eventMutex;
Event _eventArray[MAX_EVENTS];
Event *_firstEvent;
Event *_lastEvent;
Event *_eventCursor;

short _c1State;
short _c1POV = -1;
short _c2State;
short _c2POV = -1;

// ---------------------------
// Function declarations

task EventThread();
void Event_clear(Event *e);
Event *findUnusedEvent();
Event *nextEvent(const Event *e);
void addEvent(const Event *e);
void consumeEvent(Event *ret);

// ---------------------------

task EventThread()
{
    hogCPU();
#ifdef DEBUG
    writeDebugStreamLine("EventThread() started");
    PlaySound(soundBeepBeep);
#endif

    // Initialize storage and variables
    Mutex_init(&_eventMutex);

    for (int i = 0; i < MAX_EVENTS; i++)
        Event_clear(&_eventArray[i]);

    _firstEvent = &_eventArray[0];
    _lastEvent = &_eventArray[MAX_EVENTS - 1];
    _eventCursor = _firstEvent;

    releaseCPU();

    // Constantly scan events
    while (true)
    {
        getJoystickSettings(joystick);

        // Check button bitmaps for changes
        // Controller 1 ------------------------------------------------
        for (int i = 0; i < NUM_BUTTONS; i++) {
            short mask = 1 << i;
            bool state = (_c1State & mask) == mask;
            bool pressed = (joystick.joy1_Buttons & mask) == mask;
            if (state != pressed) {
                // Button was pressed
                Event newEvent;
                newEvent.type = (pressed) ? EVENT_TYPE_CONTROLLER_1_BUTTON_DOWN : EVENT_TYPE_CONTROLLER_1_BUTTON_UP;
                newEvent.data = i + 1;
                addEvent(&newEvent);

                // Fix the state
                if (pressed) {
                    // tell the state that its pressed
                    _c1State = _c1State | mask;
                } else {
                    // tell the state that it isnt pressed
                    _c1State = _c1State & ~mask;
                }
            }
        }

        if (_c1POV != joystick.joy1_TopHat) {
            Event newEvent;
            newEvent.type = EVENT_TYPE_CONTROLLER_1_POV_CHANGE;
            newEvent.data = joystick.joy1_TopHat;
            addEvent(&newEvent);
            _c1POV = joystick.joy1_TopHat;
        }

        // Controller 2 -------------------------------------------------
        for (int i = 0; i < NUM_BUTTONS; i++) {
            short mask = 1 << i;
            bool state = (_c2State & mask) == mask;
            bool pressed = (joystick.joy2_Buttons & mask) == mask;
            if (state != pressed) {
                // Button was pressed
                Event newEvent;
                newEvent.type = (pressed) ? EVENT_TYPE_CONTROLLER_2_BUTTON_DOWN : EVENT_TYPE_CONTROLLER_2_BUTTON_UP;
                newEvent.data = i + 1;
                addEvent(&newEvent);

                // Fix the state
                if (pressed) {
                    // tell the state that its pressed
                    _c2State = _c2State | mask;
                } else {
                    // tell the state that it isnt pressed
                    _c2State = _c2State & ~mask;
                }
            }
        }

        if (_c2POV != joystick.joy2_TopHat) {
            Event newEvent;
            newEvent.type = EVENT_TYPE_CONTROLLER_2_POV_CHANGE;
            newEvent.data = joystick.joy2_TopHat;
            addEvent(&newEvent);
            _c2POV = joystick.joy2_TopHat;
        }

        // ----------------------------------------------------------------
    }
}

Event *nextEvent(const Event *e)
// Internal function - don't use this in a drive program
// This function returns the next event in the queue.
// This, along with consume event, is essentially the entire queue
// implementation
{
    if (e == _lastEvent)
        return _firstEvent;
    else
        return e + 1;
}

Event *findUnusedEvent()
// Internal function - don't use this in a drive program
// This function returns the location of the closest empty
// event after the cursor.  Essentially returns the event
// after the back of the queue
{
    Event *curr = _eventCursor;
    if (eventIsEmpty(curr))
        return curr;
    else
        curr = nextEvent(curr);

    while (curr != _eventCursor)
    {
        if (eventIsEmpty(curr))
            return curr;
        curr = nextEvent(curr);
    }

    // If we got here, that means we couldn't find any
    // empty events
    return NULL;
}

void addEvent(const Event *e)
// Internal function - don't use this in a drive program
// This function adds an event to the back of the queue (if there is space)
{
    Mutex_lock(&_eventMutex);

    Event *empty = findUnusedEvent();
    if (empty == NULL) {
        writeDebugStreamLine("Could not find empty event");
        Mutex_unlock(&_eventMutex);
        return; // We can't do anything
    }

    empty->type = e->type;
    empty->data = e->data;

#ifdef DEBUG
    writeDebugStreamLine("Added new button press event with code: %d type: %d",
        e->data, e->type);
#endif

    Mutex_unlock(&_eventMutex);
}

void consumeEvent(Event *ret)
// Returns the event at the front of the queue
// This event could be filled or empty
{
    Mutex_lock(&_eventMutex);

    ret->type = _eventCursor->type;
    ret->data = _eventCursor->data;

    Event_clear(_eventCursor);
    _eventCursor = nextEvent(_eventCursor);

    Mutex_unlock(&_eventMutex);
}

void Event_clear(Event *e)
// Clears the given event
// Sets the type to NONE and data to 0
{
    e->type = EVENT_TYPE_NONE;
    e->data = 0;
}

#endif // EVENT_H
