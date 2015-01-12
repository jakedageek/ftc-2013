#ifndef LIFT_H
#define LIFT_H

#define RESET 0
#define THIRTY_LIFT 1 	//calibrate
#define SIXTY_LIFT 2 	//calibrate
#define NINETY_LIFT 3 	//calibrate
#define GOAL_LIFT 4 	//calibrate
#define LIFT_UP 100 	//calibrate
#define LIFT_DOWN -20 	//calibrate
#define LIFT_STALL 10		//calibrate
#define GATE_OPEN 40 		//calibrate
#define GATE_CLOSE 60 	//calibrate
#define BANANA_DOWN 1		//calibrate
#define BANANA_UP 2			//calibrate

void liftMove(int target);
void liftMan(bool up);
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

void liftMan(bool up){
	if(up == true){
		motor[liftLeft] = LIFT_UP;
		motor[liftRight] = LIFT_UP;
	}else{
		motor[liftLeft] = LIFT_DOWN;
		motor[liftRight] = LIFT_DOWN;
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
