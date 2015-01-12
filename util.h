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

#ifndef UTIL_H
#define UTIL_H

#include "JoystickDriver.c"

#define CONTROLLER_A 02
#define CONTROLLER_X 01
#define CONTROLLER_B 03
#define CONTROLLER_Y 04
#define CONTROLLER_R1 06
#define CONTROLLER_R2 08
#define CONTROLLER_L1 05
#define CONTROLLER_L2 07
#define CONTROLLER_L3 11
#define CONTROLLER_R3 12

#define DPAD_UP 0
#define DPAD_DOWN 4
#define DPAD_LEFT 6
#define DPAD_RIGHT 2

#define degreesToRadians(x) (x * PI / (float) 180)
#define radiansToDegrees(x) (x * (float) 180 / PI)


const bool bLogarithmicScale = true;
const bool kMaximumPowerLevel = 100;  // Adjust to set max power level to be used.

int joystickValue(int controller, int joy, int axis)
// Grab a joystick value from the controller state
// Return Value:
// - the requested state value
// Parameters:
// - controller: controller 1 or 2
// - joy: joystick 1 or 2 (left or right)
// - axis: 1 = x, 2 = y
{
	int val = 0;
	getJoystickSettings(joystick);

	if (controller == 1)
	{
		if (joy == 1) {
			if (axis == 1) {
				val = joystick.joy1_x1;
				} else {
				val = joystick.joy1_y1;
			}
		}
		else {
			if (axis == 1) {
				val = joystick.joy1_x2;
				} else {
				val = joystick.joy1_y2;
			}
		}
	}
	else if (controller == 2)
	{
		if (joy == 1) {
			if (axis == 1)
				val = joystick.joy2_x1;
			else
				val = joystick.joy2_y1;
		}
		else {
			if (axis == 1)
				val = joystick.joy2_x2;
			else
				val = joystick.joy2_y2;
		}
	}
	else
	{
		PlaySound(soundException);
		StopAllTasks();
	}

	float negative;
	float ratio;

	negative = (float) val / (float) abs(val);
	ratio = (val * val) / (127.0 * 127.0);
	val = 100.0 * ratio * negative;

	if (val > -10
		&& val < 10)
	val = 0;

	return val;
}


int scaleJoystick(int nJoy1, int nMaxValue = kMaximumPowerLevel)
{
	//
	// This function scales the joystick settings to the appropriate range for
	// controlling a NXT motor.
	//
	// Joystick values range from -128 to +127.
	// Speed/power settings for NXT motors range from -100 to +100
	//
	// The physical range of motion of a joystick is quite small and it is sometimes
	// hard to control slow speeds. So another capability of this program to apply
	// a "logarithmic" scale to the joystick settings.
	//
	static const int nLogScale[17] =
	{
		  0,   5,   9,   10,
		 12,  15,  18,  24,
		 30,  36,  43,  50,
		 60,  72,  85, 100,
		100
	};
	int nScaled;

	nScaled = nJoy1;
	if (bLogarithmicScale)
	{
	  nScaled /= 8;
	  if (nScaled >= 0)
	    nScaled = nLogScale[nScaled];
	  else
	    nScaled = - nLogScale[ - nScaled];
  }
	nScaled *= nMaxValue;
	nScaled /= 100;
  return nScaled;
}

#endif
