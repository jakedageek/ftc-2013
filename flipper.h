#ifndef FLIPPER_H
#define FLIPPER_H

#define FLIPPER_WAIT_TIME 1000
#define SERVO_FLIPPER_EXTENDED 180;
#define SERVO_FLIPPER_RETRACTED 0;

void flipper_flip();
void flipper_extend();
void flipper_wait();
void flipper_retract();

void flipper_flip() {
	flipper_extend();
	flipper_wait();
	flipper_retract();
}

void flipper_extend() {
	servo[flipper] = SERVO_FLIPPER_EXTENDED;
}

void flipper_wait() {
	wait1Msec(FLIPPER_WAIT_TIME);
}

void flipper_retract() {
	servo[flipper] = SERVO_FLIPPER_RETRACTED;
}

#endif
