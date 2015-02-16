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

void initializeRobot(){
	calibrateGyro();
	nMotorEncoder[liftLeft] = 0;		//reset encoder
	hook(true);			//reset servos
	gate(false);
	banana(false);
	servo[hookFront] = 50;
	//RESET SERVOS
	return;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* STRAIGHT FORWARD AUTONOMOUS 																																											*/
/* ---------------------------------------------------------------------------------------------------------------- */


void autoStraight(){
	liftMan(0);
	wait1Msec(200);
	liftMan(2);
	wait1Msec(10);
	driveBackwardDist(30, 30);	//drive out from the parking zone
	wait1Msec(50);
	turnEuler(3,50,false);

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
	driveBackwardDist(14, 50); //drive towards pole
	turnEuler(90,55,true); //turn towards pole
	driveBackwardDist(30,40); //drive against pole and knock it down
	wait1Msec(10);

	return;
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
	turnEuler(45,70,true); //turn left
	wait1Msec(10);
	driveBackwardDist(32, 30); //drive left backwards
	wait1Msec(10);
	turnEuler(95,70,false); //turn towards the goal SYNC
	wait1Msec(10);
	driveBackwardUltra(30, 35);
	//driveBackwardDist(7, 30); // move towards the goal
	//score
	wait1Msec(50);


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

	driveForwardDist(5,50);


	liftMan(2);

	//pole

	turnEuler(90,55,true); //turn towards pole
	wait1Msec(10);
	driveForwardDist(17, 50); //drive towards pole
	turnEuler(95,55,true); //turn towards pole
	driveForwardDist(45,40); //drive against pole and knock it down
	turnEuler(25,55,false);
	driveBackwardDist(20,40);
	wait1Msec(10);


	return;
}

/* ---------------------------------------------------------------------------------------------------------------- */
/* HORIZONTAL AUTONOMOUS 																																											*/
/* ---------------------------------------------------------------------------------------------------------------- */

void autoHoriz(){

	driveBackwardDist(20,50); //drive out of zone
	wait1Msec(100);
	turnEuler(35, 50, true);
	wait1Msec(50);
	driveBackwardDistAC(44,50);
	wait1Msec(50);
	turnEuler(115, 50, false);

	driveBackwardUltra(30, 25);

	wait1Msec(50);

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

	turnEuler(80,55,true); //turn towards pole
	wait1Msec(10);
	driveForwardDist(17, 50); //drive towards pole
	turnEuler(98,55,true); //turn towards pole
	driveForwardDist(30,40); //drive against pole and knock it down
	turnEuler(30,55,false);
	driveBackwardDist(10,40);
	wait1Msec(10);

	return;
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

	return;
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
	turnEuler(95,70,false); //turn towards the goal SYNC
	wait1Msec(10);
	driveBackwardUltra(30, 35);
	//driveBackwardDist(7, 30); // move towards the goal
	//score
	wait1Msec(50);


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

	return;
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

	wait1Msec(50);

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

	return;
}


/* ---------------------------------------------------------------------------------------------------------------- */
/* DEFENSE AUTONOMOUS 																																															*/
/* ---------------------------------------------------------------------------------------------------------------- */

void autoD(){

	driveBackwardDist(10, 50);
	turnEuler(53, 70, true);
	driveBackwardDist(55, 100);

	return;
}



#endif
