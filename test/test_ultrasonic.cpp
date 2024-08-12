#include "motor.h"
#include "ultrasonic.h"

class PrintDistanceCallback:public UltrasonicCallback
{
	virtual void distance_ready(float d) 
	{
		printf("%f\n",d);
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

	}
	return 0;
}
