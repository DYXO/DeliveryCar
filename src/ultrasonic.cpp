#include "ultrasonic.h"

ultrasonic::ultrasonic()
{
	gpio_init();
}

ultrasonic::~ultrasonic()
{
	
}

void ultrasonic::registerCallback(UltrasonicCallback* cb)
{
	callback=cb;
}

void ultrasonic::unregisterCallback()
{
	callback=nullptr;
}

void ultrasonic::start()
{
	if(running)
	return;
	disThread = std::thread(&ultrasonic::echo_wait,this);
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

void ultrasonic::echo_wait()
{
	running=1;
	while(1)
	{
		while(gpioRead(echogpio)!=1)
		{
			wave_start();
		}
		gpioTime(1,p_s,p_m);
		last_seconds=seconds;
		last_micros=micros;
		//wait for the signal from echogpio
		//turned into 0
		while(gpioRead(echogpio)==1);
		gpioTime(1,p_s,p_m);
		distance=((seconds-last_seconds)+(micros-last_micros)*0.000001)*340/2;
		if(callback!=nullptr)
		{
			callback->distance_ready(distance);
		}
	}
}
