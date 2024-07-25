#include "motor.h"

motor::motor()
{
	initstate=gpioInitialise();
	if(!initstate)
		printf("erro!gpio_init failed!\n");
}

motor::~motor()
{
	stop();
	gpioTerminate();
}

void motor::set_speed(float leftspeed,float rightspeed)
{	
	int l_setpwm,r_setpwm;
	if(!initstate)
		printf("erro!gpio_init failed!\n");
	else if(leftspeed<-100||leftspeed>100||rightspeed<-100||rightspeed>100)
		printf("speed erro!\n");
	else
	{
		if(leftspeed<0)
		{
			l_setpwm=(-leftspeed)/100*255;
			gpioPWM(l_motorgpio1, l_setpwm);
	        gpioPWM(l_motorgpio2, 0);
		}
		else
		{
			l_setpwm=(leftspeed/100)*255;
			gpioPWM(l_motorgpio1, 0);
	        gpioPWM(l_motorgpio2, l_setpwm);
		}
		if(rightspeed<0)
		{
			r_setpwm=(-rightspeed/100)*255;
			gpioPWM(r_motorgpio1, r_setpwm);
	        gpioPWM(r_motorgpio2, 0);
		}
		else
		{
			r_setpwm=(rightspeed/100)*255;
			gpioPWM(r_motorgpio1, 0);
	        gpioPWM(r_motorgpio2, r_setpwm);
		}		
	}
}

void motor::stop()
{
	gpioPWM(l_motorgpio1, 0);
	gpioPWM(l_motorgpio2, 0);
	gpioPWM(r_motorgpio1, 0);
	gpioPWM(r_motorgpio2, 0);
}
