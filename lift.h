#ifndef LIFT_H
#define LIFT_H

#define RESET 25
#define THIRTY_LIFT 1400
#define SIXTY_LIFT 2350
#define NINETY_LIFT 3450
#define GOAL_LIFT 4550 + 300
#define MAX_LIFT 5000
#define INTAKE_LIFT 800
#define LIFT_UP 100
#define LIFT_DOWN -5
#define LIFT_STALL 10

void liftMove(int target);
void liftMan(int up);
void hook(bool up);
void fronthook(int pos);
void gate(bool open);
void banana(bool score);
void bananaman(bool score);
void bananaKnock();
void intakeKnock();
void flickIt();

bool bananascore = false;

//presets for the lift operation
void liftMove(int target){
	//if the lift is moving UP
	if(target > nMotorEncoder[liftLeft]){
		while(nMotorEncoder[liftLeft] < target){
			writeDebugStreamLine("Left Encoder %d", nMotorEncoder[liftLeft]);
			motor[liftLeft] = LIFT_UP;
			motor[liftRight] = LIFT_UP;

			if(joy2Btn(CONTROLLER_X)){
		  		break;
		  }
		}
		motor[liftLeft] = LIFT_STALL;
		motor[liftRight] = LIFT_STALL;
		banana(true);
	}else{ 				//if the lift is moving DOWN
		banana(false);
		wait1Msec(100);
		while(nMotorEncoder[liftLeft] > target){
			writeDebugStreamLine("Left Encoder %d", nMotorEncoder[liftLeft]);
			motor[liftLeft] = LIFT_DOWN;
			motor[liftRight] = LIFT_DOWN;
			if(joy2Btn(CONTROLLER_X)){
		  		break;
		  }
		}
		motor[liftLeft] = LIFT_STALL;
		motor[liftRight] = LIFT_STALL;
	}
	return;
}

//manual operation of the lift
void liftMan(int up){
	if(up == 0){
		if(nMotorEncoder[liftLeft] > MAX_LIFT){
			motor[liftLeft] = LIFT_STALL;
			motor[liftRight] = LIFT_STALL;
		}else{
		motor[liftLeft] = LIFT_UP;
		motor[liftRight] = LIFT_UP;
		}
	}else if(up == 1){
		if(bananascore && nMotorEncoder[liftLeft] < THIRTY_LIFT){
			motor[liftLeft] = LIFT_STALL;
			motor[liftRight] = LIFT_STALL;
		}else{
			motor[liftLeft] = LIFT_DOWN;
			motor[liftRight] = LIFT_DOWN;
		}
	}else if(up == 2){
		if(nMotorEncoder[liftLeft] < 220){	//if lift is completely collapsed, no stall torque
			motor[liftLeft] = 0;
			motor[liftRight] = 0;
		}else{															//else, stall to maintain height
			motor[liftLeft] = LIFT_STALL;
			motor[liftRight] = LIFT_STALL;
		}
	}
	return;
}

void hook(bool up){
	if(up == true){
		//hook up positions
		servo[hookLeft] = 208; //calibrate
		servo[hookRight] = 34; //calibrate
	}else{
		servo[hookLeft] = 250; //calibrate
		servo[hookRight] =0; //calibrate
	}
}

void fronthook(int pos){
	if(pos == 0){
		//initialize
		if(servo[hookFront] > 0){
			while(servo[hookFront] > 0){
				servo[hookFront] = servo[hookFront] - 2;
				wait1Msec(10);
			}
		}else{
			while(servo[hookFront] < 0){
				servo[hookFront] = servo[hookFront] + 2;
				wait1Msec(10);
			}
		}
		servo[hookFront] = 0;
	}else if(pos == 1){
		//score
		if(servo[hookFront] > 160){
			while(servo[hookFront] > 160){
				servo[hookFront] = servo[hookFront] - 2;
				wait1Msec(10);
			}
		}else{
			while(servo[hookFront] < 160){
				servo[hookFront] = servo[hookFront] + 2;
				wait1Msec(10);
			}
		}
	servo[hookFront] = 160;
	}else if(pos == 2){
		//grab
		if(servo[hookFront] > 244){
			while(servo[hookFront] > 244){
				servo[hookFront] = servo[hookFront] - 2;
				wait1Msec(10);
			}
		}else{
			while(servo[hookFront] < 244){
				servo[hookFront] = servo[hookFront] + 2;
				wait1Msec(10);
			}
		}
	servo[hookFront] = 244;
	}else if(pos == 3){
		//tele
		if(servo[hookFront] > 60){
			while(servo[hookFront] > 60){
				servo[hookFront] = servo[hookFront] - 2;
				wait1Msec(10);
			}
		}else{
			while(servo[hookFront] < 60){
				servo[hookFront] = servo[hookFront] + 2;
				wait1Msec(10);
			}
		}
	servo[hookFront] = 60;
	}
}

void gate(bool open){
	if(open == true){
		//hook up positions
		servo[gateBack] = 50; //calibrate
	}else{
		servo[gateBack] = 0; //calibrate
	}
}

void banana(bool score){
	if(score == true){
		//banana score
		if(servo[bananaServo] > 116){
			while(servo[bananaServo] > 116){
				servo[bananaServo] = servo[bananaServo] - 2;
				wait1Msec(10);
			}
		}else{
			while(servo[bananaServo] < 116){
				servo[bananaServo] = servo[bananaServo] + 2;
				wait1Msec(10);
			}
		}
		//servo[bananaServo] = 124; //calibrate
		bananascore = true;
	}else{
		if(servo[bananaServo] > 196){
			while(servo[bananaServo] > 196){
				servo[bananaServo] = servo[bananaServo] - 2;
				wait1Msec(10);
			}
		}else{
			while(servo[bananaServo] < 196){
				servo[bananaServo] = servo[bananaServo] + 2;
				wait1Msec(10);
			}
		}
		//servo[bananaServo] = 200; //calibrate
		bananascore = false;
	}
}

//knocks the banana down to score easier
void bananaKnock(){
	if(bananascore){
		servo[bananaServo] = servo[bananaServo] - 3;
		wait1Msec(1300);
		servo[bananaServo] = servo[bananaServo] + 3;
	}else{
		writeDebugStreamLine("knock failed");
	}
}

void intakeKnock(){
	liftMan(0);
	wait1Msec(200);
	servo[bananaServo] = servo[bananaServo] - 10;
	wait1Msec(300);
	servo[bananaServo] = servo[bananaServo] + 10;
}

void bananaman(bool score){
	if(score){
		servo[bananaServo] = servo[bananaServo] - 1;
		wait1Msec(50);
	}else{
		servo[bananaServo] = servo[bananaServo] + 1;
		wait1Msec(50);
	}
}

void flickIt(){
	servo[bananaServo] = 140;
	wait1Msec(500);
	servo[bananaServo] = 130;
	wait1Msec(100);
	servo[bananaServo] = 120;
}


#endif
