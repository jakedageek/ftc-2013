#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     driveLeft,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     liftLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     driveRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     liftRight,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "util.h"
#include "event.h"
#include "block-loader.h"


task main()
{
	waitForStart();

	while(true){
		// Drive controls
    motor[driveLeft1] = joystickValue(1, 1, 2);
    motor[driveLeft2] = joystickValue(1, 1, 2);
    motor[driveRight1] = joystickValue(1, 2, 2);
    motor[driveRight2] = joystickValue(1, 2, 2);

    // Lift controls


}
