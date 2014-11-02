// sampling time: 10 msec

void poscon( float degree, float speed )
{
	int i, cnt;
	int systime, lasttime, delta;
	int slopetime, command;
	float halfdeg;
	float maxspeed;
	float currpos, speed;
	float downpos;
	
	maxspeed = 80;	// 80 %
	slopetime = maxspeed * 1;	// 0.8 sec
	halfdeg = degree / 2.;
	
	lasttime = systime - 10;	// to make initial delta to 10 msec
	currpos = 0.0;
	
	cnt = 0;
	command = 0;
	
	for( i=0; i<slopetime; i++ ) {
		systime = get_systime();
		delta = systime - lasttime;
		lasttime = systime;
		
		speed = getSpeed();		// deg/sec
		currpos += speed / 1000. * (float)delta;
		if( currpos >= halfdeg )
			break;
			
		//cnt ++;
		//if( cnt >= 2 ) {
		//	cnt = 0;
			
			command += 1;
			motor_command( command );
		//}
		delay( 10 - delta );
	}
	
	motor_command( command );
	downpos = degree - currpos;
	while(1) {
		speed = getSpeed();		// deg/sec
		currpos += speed / 1000. * delta;
		if( currpos >= downpos )
			break;		

		delay( 10 - delta );
	}
		
	for( i=0; i<slopetime; i++ ) {
		systime = get_systime();
		delta = systime - lasttime;
		lasttime = systime;
		
		speed = getSpeed();		// deg/sec
		currpos += speed / 1000. * delta;
		if( currpos >= degree )
			stop_motor();
			break;
			
		//cnt ++;
		//if( cnt >= 2 ) {
		//	cnt = 0;
			
			command -= 1;
			if( command < 0 ) {
				stop_motor();
				break;
			}
			motor_command( command );
		//}
		delay( 10 - delta );
	}
	
}
