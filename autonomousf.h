#ifndef AUTONOMOUSF_H
#define AUTONOMOUSF_H

#include "util.h"
#include "lift.h"
#include "autonomous3.h"

const tMUXSensor HTANG = msensor_S3_1;
const tMUXSensor Sonar = msensor_S3_2;

//TOWER AUTONOMOUS
int sonarvalue = 0;
void initializeRobot();
void autoStraight();
void autoDiag();
void autoHoriz();
void autoStraightP();
void autoDiagP();
void autoHorizP();
void autoD();
void autoPark30();
void autoRampDouble();
void autoRampOff();

void initializeRobot(){
	calibrateGyro();
	nMotorEncoder[liftLeft] = 0;		//reset encoder
	hook(true);			//reset servos
	gate(false);
	banana(false);
	fronthook(0);
	//RESET SERVOS
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* STRAIGHT FORWARD AUTONOMOUS 																																											*/
/* ---------------------------------------------------------------------------------------------------------------- */


void autoStraight(){
	driveBackwardDist(30, 30);	//drive out from the parking zone
	wait1Msec(50);
	turnEuler(3,50,false);

	fronthook(3);

	liftMove(GOAL_LIFT);
	wait1Msec(100);

	driveBackwardDist(8,15); //move closer

	wait1Msec(1000);

	gate(true);
	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);

	driveForwardDist(5,15); //move closer

	wait1Msec(500);

	liftMove(RESET);

	turnEuler(90,55,false); //turn towards pole
	wait1Msec(10);
	driveBackwardDist(16, 50); //drive towards pole
	turnEuler(90,55,true); //turn towards pole
	driveBackwardDist(30,40); //drive against pole and knock it down
	wait1Msec(10);
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* DIAGONAL AUTONOMOUS 																																											*/
/* ---------------------------------------------------------------------------------------------------------------- */

void autoDiag(){
	liftMan(0);
	wait1Msec(200);
	liftMan(2);
	writeDebugStreamLine("Function AutoDiag");
	driveBackwardDist(10, 30);	//drive out from the parking zone
	wait1Msec(10);
	turnEuler(45,60,true); //turn left
	wait1Msec(10);
	driveBackwardDist(32, 30); //drive left backwards
	wait1Msec(10);
	turnEuler(90,60,false); //turn towards the goal SYNC
	wait1Msec(10);
	driveBackwardUltra(30, 35);
	//driveBackwardDist(7, 30); // move towards the goal
	//score
	wait1Msec(50);

	fronthook(3);

	liftMove(GOAL_LIFT);
	wait1Msec(100);

	driveBackwardDist(8,15); //move closer

	wait1Msec(1000);
	gate(true);

	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);

	driveForwardDist(5,15); //move away

	wait1Msec(500);

	liftMove(RESET);

	driveForwardDist(5,50);

	//pole

	turnEuler(90,55,true); //turn towards pole
	wait1Msec(10);
	driveForwardDist(19, 50); //drive towards pole
	turnEuler(95,55,true); //turn towards pole
	driveForwardDist(45,40); //drive against pole and knock it down
	turnEuler(25,55,false);
	driveBackwardDist(20,40);
	wait1Msec(10);
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* HORIZONTAL AUTONOMOUS 																																											*/
/* ---------------------------------------------------------------------------------------------------------------- */

void autoHoriz(){

	driveBackwardDist(20,50); //drive out of zone
	wait1Msec(100);
	turnEuler(35, 50, true);
	wait1Msec(50);
	driveBackwardDistAC(46,50);
	wait1Msec(50);
	turnEuler(115, 50, false);

	driveBackwardUltra(25, 25);

	fronthook(3);

	wait1Msec(150);

	liftMove(GOAL_LIFT);
	wait1Msec(100);

	driveBackwardUltra(15,13);

	wait1Msec(2000);
	gate(true);

	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);

	driveForwardDist(5,15); //move closer

	wait1Msec(500);

	liftMove(RESET);

	turnEuler(70,55,true); //turn towards pole
	wait1Msec(10);
	driveForwardDist(16, 50); //drive towards pole
	turnEuler(98,55,true); //turn towards pole
	driveForwardDist(30,40); //drive against pole and knock it down
	turnEuler(30,55,false);
	driveBackwardDist(10,40);
	wait1Msec(10);
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* STRAIGHT FORWARD AUTONOMOUS NO POLE																																							*/
/* ---------------------------------------------------------------------------------------------------------------- */


void autoStraightP(){
	liftMan(0);
	wait1Msec(200);
	liftMan(2);
	wait1Msec(10);
	driveBackwardDist(30, 30);	//drive out from the parking zone
	wait1Msec(50);
	turnEuler(3,50,false);

	fronthook(3);

	liftMove(GOAL_LIFT);
	wait1Msec(100);

	driveBackwardDist(8,15); //move closer

	wait1Msec(1000);

	gate(true);
	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);

	driveForwardDist(5,15); //move closer

	wait1Msec(500);

	liftMove(RESET);
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* DIAGONAL AUTONOMOUS NO POLE																																											*/
/* ---------------------------------------------------------------------------------------------------------------- */

void autoDiagP(){
	liftMan(0);
	wait1Msec(200);
	liftMan(2);
	writeDebugStreamLine("Function AutoDiag");
	driveBackwardDist(10, 30);	//drive out from the parking zone
	wait1Msec(10);
	turnEuler(45,70,true); //turn left
	wait1Msec(10);
	driveBackwardDist(32, 30); //drive left backwards
	wait1Msec(10);
	turnEuler(90,70,false); //turn towards the goal SYNC
	wait1Msec(10);
	driveBackwardUltra(30, 35);
	//driveBackwardDist(7, 30); // move towards the goal
	//score
	wait1Msec(50);

	fronthook(3);

	liftMove(GOAL_LIFT);
	wait1Msec(100);

	driveBackwardDist(8,15); //move closer

	wait1Msec(1000);
	gate(true);

	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);

	driveForwardDist(5,15); //move away

	wait1Msec(500);

	liftMove(RESET);
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* HORIZONTAL AUTONOMOUS 		NO POLE																																									*/
/* ---------------------------------------------------------------------------------------------------------------- */

void autoHorizP(){

	driveBackwardDist(20,50); //drive out of zone
	wait1Msec(100);
	turnEuler(35, 50, true);
	wait1Msec(50);
	driveBackwardDistAC(44,50);
	wait1Msec(50);
	turnEuler(115, 50, false);

	driveBackwardUltra(30, 25);

	fronthook(3);

	wait1Msec(150);

	liftMove(GOAL_LIFT);
	wait1Msec(100);

	driveBackwardUltra(15,13);

	wait1Msec(2000);
	gate(true);

	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);

	driveForwardDist(5,15); //move closer

	wait1Msec(500);

	liftMove(RESET);
}


/* ---------------------------------------------------------------------------------------------------------------- */
/* DEFENSE AUTONOMOUS 																																															*/
/* ---------------------------------------------------------------------------------------------------------------- */

void autoD(){

	driveBackwardDist(10, 50);
	turnEuler(53, 70, true);
	driveBackwardDist(55, 100);
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Parking zone 30 goal auto																																												*/
/* ---------------------------------------------------------------------------------------------------------------- */


void autoPark30(){
	driveBackwardDist(15, 60);

	turnEuler(145, 60, true);

	driveForwardDistAC(35, 70);

	turnEuler(40, 60, true);

	driveForwardDistAC(36, 80);

	fronthook(1);

	driveBackwardDist(5,30);

	fronthook(3);

	turnEuler(135, 60, true);

	driveBackwardDist(35, 20);

	hook(false);
	liftMove(NINETY_LIFT);
	wait1Msec(1000);
	gate(true);
	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);
	liftMove(RESET);

	driveForwardDist(4,30);

	turnEuler(40, 60, true);

	driveForwardDistAC(90,100);
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Ramp 3060 auto																																																		*/
/* ---------------------------------------------------------------------------------------------------------------- */

void autoRampDouble(){
	/* LIFT LIFT BEFORE MOVING OFF RAMP */
	liftMan(0);
	wait1Msec(200);
	liftMan(2);

	driveBackwardDistAC(50,30);

	wait1Msec(100);

	driveBackwardDistAC(22, 70);

	driveBackwardDist(17, 20);

	fronthook(3);

	wait1Msec(100);

	hook(false);
	liftMove(SIXTY_LIFT);
	wait1Msec(1000);
	gate(true);
	wait1Msec(100);
	bananaKnock();
	wait1Msec(100);
	gate(false);
	wait1Msec(50);
	liftMove(500);

	turnEuler(190, 50, true);

	driveForwardDist(10, 50);

	fronthook(2);

	wait1Msec(700);

	turnEuler(35, 40, false);

	driveBackwardDistAC(105, 100);

	turnEuler(60, 50, false);

	driveBackwardDist(5,50);

	liftMove(RESET);

}

/* ---------------------------------------------------------------------------------------------------------------- */
/* Drive off the ramp																																																*/
/* ---------------------------------------------------------------------------------------------------------------- */

void autoRampOff(){

	driveBackwardDist(45,30);

}




#endif
