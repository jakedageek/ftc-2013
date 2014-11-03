// sampling time: 10 msec

/*
Copyright (c) 2014 Jake Lee, Joon Lee, AJ Stubbard, Team 4790

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


//PROTOTYPE CODE - DOES NOT WORK IN APPLICATION
//THIS CODE WAS WRITTEN AS A PROOF TO CONCEPT - MUST BE CONVERTED TO ACTUAL CODE
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
