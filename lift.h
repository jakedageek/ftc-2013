#ifndef LIFT_H
#define LIFT_H

#define RESET 190
#define THIRTY_LIFT 625
#define SIXTY_LIFT 1275
#define NINETY_LIFT 1980
#define GOAL_LIFT 2675
#define LIFT_UP 60
#define LIFT_DOWN -5
#define LIFT_STALL 10

void liftMove(int target);
void liftMan(int up);
void hook(bool up);
void gate(bool open);
void banana(bool up);

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
	}else{ 				//if the lift is moving DOWN
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

void liftMan(int up){
	if(up == 0){
		motor[liftLeft] = LIFT_UP;
		motor[liftRight] = LIFT_UP;
	}else if(up == 1){
		motor[liftLeft] = LIFT_DOWN;
		motor[liftRight] = LIFT_DOWN;
	}else if(up == 2){
		motor[liftLeft] = LIFT_STALL;
		motor[liftRight] = LIFT_STALL;
	}
	return;
}

void hook(bool up){
	if(up == true){
		//hook up positions
		servo[hookLeft] = 1; //calibrate
		servo[hookRight] = 1; //calibrate
	}else{
		servo[hookLeft] = 180; //calibrate
		servo[hookRight] = 180; //calibrate
	}
}

void gate(bool open){
	if(open == true){
		//hook up positions
		servo[gateBack] = 1; //calibrate
	}else{
		servo[gateBack] = 180; //calibrate
	}
}

void banana(bool up){
	if(up == true){
		//hook up positions
		servo[bananaServo] = 1; //calibrate
	}else{
		servo[bananaServo] = 180; //calibrate
	}
}


#endif
