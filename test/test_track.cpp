#include "motor.h"
#include "linetrack.h"
#include "ultrasonic.h"

int main(int argc, char *argv[]) 
{
	//motor M1;
	//M1.set_speed(0,0);
	linetrack car;
	
	while(1)
	{
		car.track_control();
		gpioSleep(PI_TIME_RELATIVE, 0, 50000); 
	}
	return 0;
}
