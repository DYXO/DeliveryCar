#include "linetrack.h"

linetrack::linetrack()
{
	if(!gpioInitialise())
		printf("erro!gpio_init failed!\n");
}

linetrack::~linetrack()
{
	
}

void linetrack::track_control()
{
	l_value=gpioRead(l_infraredgpio);
	r_value=gpioRead(r_infraredgpio);
	if(l_value==1&&r_value==1)
	{
		carmotor.set_speed(80,80);
	}
	else if(l_value==1&&r_value==0)
	{
		carmotor.set_speed(-40,80);
	}
	else if(l_value==0&&r_value==1)
	{
		carmotor.set_speed(80,-40);
	}
	else
	{
		carmotor.set_speed(0,0);
	}
}
