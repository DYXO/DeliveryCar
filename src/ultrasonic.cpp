#include "ultrasonic.h"

ultrasonic::ultrasonic()
{
	gpio_init();
}

ultrasonic::~ultrasonic()
{
	
}

void ultrasonic::gpio_init()
{
	gpioInitialise();
	gpioSetMode(triggpio, PI_OUTPUT);
	gpioSetMode(echogpio, PI_INPUT);
}

void ultrasonic::wave_start()
{
	gpioWrite(triggpio, 1); 
	gpioDelay(20);
	gpioWrite(triggpio, 0);
}

float ultrasonic::echo_wait()
{
	wave_start();
	while(1)
	{
		if(gpioRead(echogpio)==1)
		{	
			gpioTime(1,p_s,p_m);
			last_seconds=seconds;
			last_micros=micros;
			while(gpioRead(echogpio)==1)
			{}
			gpioTime(1,p_s,p_m);
			distance=((seconds-last_seconds)+(micros-last_micros)*0.000001)*340/2;
			printf("%f\n",distance);
			return distance;
		}
	}
}
