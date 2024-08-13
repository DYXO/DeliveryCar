#include "motor.h"
#include "linetrack.h"
#include "ultrasonic.h"

bool have_block=0;
linetrack car;
void control()
{	
	car.track_control(!have_block);
	gpioSleep(PI_TIME_RELATIVE, 0, 50000); 
}

class PrintDistanceCallback:public UltrasonicCallback
{
	virtual void distance_ready(float d) 
	{
		printf("%f\n",d);
		if(d<0.3)
		{
			have_block=1;
		}
		else
		{
			have_block=0;
		}
	}
};


int main(int argc, char *argv[]) 
{
	ultrasonic u1;
	PrintDistanceCallback printdistanceCallback;
	u1.registerCallback(&printdistanceCallback);
	u1.start();
	while(1)
	{	
		control();
	}
	return 0;
}
