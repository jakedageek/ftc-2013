#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     HTSMUX2,        sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C2_1,     leftDrive,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     liftLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     inLeft,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     inRight,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     rightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     liftRight,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C1_1,    bananaServo,          tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    gateBack,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    hookFront,            tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_1,    hookRight,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    hookLeft,             tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "util.h"
#include "lift.h"
#include "autonomous3.h"
#include "autonomousf.h"

/*
Copyright (c) 2014 Jake Lee, Team 4790

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


task main()
{
	int a = 0;
	int j = 0;
	int k = 0;
	int sonarvalue;
	int sonarvalue2;

	initializeRobot();
	//waitForStart();
	banana(false);
	while(true){
		sonarvalue = USreadDist(Sonar);
		sonarvalue2 = USreadDist(Sonar2);
		writeDebugStreamLine("sonar = %d", sonarvalue);
		if(sonarvalue == 255 && sonarvalue2 == 255){
			//Diagonal center console
			a++;
			writeDebugStreamLine("a = %d", a);
			if(a > 10){
				writeDebugStreamLine("Diagonal, %d", sonarvalue);
				autoDiag();
				break;
			}
			//The ultrasonic sensor cannot detect diagonal surfaces - therefore, it returns 255 as its default value.

		}else if(abs(sonarvalue) < 118 || abs(sonarvalue2) < 118){
			//goal is straight ahead
			j++;
			writeDebugStreamLine("j = %d", j);
			if(j > 5){
				writeDebugStreamLine("Ahead, %d", sonarvalue);
				autoStraight();
				break;
			}
		}else if(abs(sonarvalue) >= 118 || abs(sonarvalue2) >= 118){
			//goal is sideways
			k++;
			writeDebugStreamLine("k = %d", k);
			if(k > 5){
				writeDebugStreamLine("Sideways, %d", sonarvalue);
				autoHoriz();
				break;
			}
		}
	}
}
