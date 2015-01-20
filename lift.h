#ifndef LIFT_H
#define LIFT_H

#define RESET 190
#define THIRTY_LIFT 4000
#define SIXTY_LIFT 6000
#define NINETY_LIFT 8000
#define GOAL_LIFT 11000
#define MAX_LIFT 12000
#define LIFT_UP 100
#define LIFT_DOWN -8
#define LIFT_STALL 8

void liftMove(int target);
void liftMan(int up);
void hook(bool up);
void gate(bool open);
void banana(bool score);

bool bananascore = false;

//presets for the lift operation
void liftMove(int target){
	//if the lift is moving UP
	if(target > nMotorEncoder[liftLeft]){
		while(nMotorEncoder[liftLeft] < target){
			writeDebugStreamLine("Left Encoder %d", nMotorEncoder[liftLeft]);
			motor[liftLeft] = LIFT_UP;
			motor[liftRight] = LIFT_UP;
		}
		motor[liftLeft] = LIFT_STALL;
		motor[liftRight] = LIFT_STALL;
		wait1Msec(100);
		banana(true);
	}else{ 				//if the lift is moving DOWN
		banana(false);
		wait1Msec(100);
		while(nMotorEncoder[liftLeft] > target){
			writeDebugStreamLine("Left Encoder %d", nMotorEncoder[liftLeft]);
			motor[liftLeft] = LIFT_DOWN;
			motor[liftRight] = LIFT_DOWN;
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
		if(nMotorEncoder[liftLeft] < 360){	//if lift is completely collapsed, no stall torque
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
		servo[hookLeft] = 218; //calibrate
		servo[hookRight] = 49; //calibrate
	}else{
		servo[hookLeft] = 255; //calibrate
		servo[hookRight] = 6; //calibrate
	}
}

void gate(bool open){
	if(open == true){
		//hook up positions
		servo[gateBack] = 180; //calibrate
	}else{
		servo[gateBack] = 0; //calibrate
	}
}

void banana(bool score){
	if(score == true){
		//banana score
		if(servo[bananaServo] > 124){
			while(servo[bananaServo] > 124){
				servo[bananaServo] = servo[bananaServo] - 1;
				wait1Msec(10);
			}
		}else{
			while(servo[bananaServo] < 124){
				servo[bananaServo] = servo[bananaServo] + 1;
				wait1Msec(10);
			}
		}
		//servo[bananaServo] = 124; //calibrate
		bananascore = true;
	}else{
		if(servo[bananaServo] > 200){
			while(servo[bananaServo] > 200){
				servo[bananaServo] = servo[bananaServo] - 1;
				wait1Msec(10);
			}
		}else{
			while(servo[bananaServo] < 200){
				servo[bananaServo] = servo[bananaServo] + 1;
				wait1Msec(10);
			}
		}
		//servo[bananaServo] = 200; //calibrate
		bananascore = false;
	}
}


#endif
