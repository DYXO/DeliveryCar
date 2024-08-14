#include "motor.h"
#include "linetrack.h"
#include "ultrasonic.h"
#include "playsound.h"
#include "serial.h"
#include "cabinet.h"

bool have_block=0;
linetrack car;
scanner s1(16);
cabinet DeliveryBox(&s1);
//soundplayer warning("Sound.wav");
bool arrive=0;
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
			//std::thread warning_sound(&soundplayer::play,&warning);
		}
		else
		{
			have_block=0;
		}
	}
};


int main(int argc, char *argv[]) 
{
	while(!gpioInitialise())
	{
		printf("erro\n");
	}
	ultrasonic u1;
	PrintDistanceCallback printdistanceCallback;
	u1.registerCallback(&printdistanceCallback);
	u1.start();
	while(1)
	{	
		DeliveryBox.deposit();
		if(DeliveryBox.lock==1&&arrive==0)
		{
			control();
		}
		else if(arrive==1)
		{
			DeliveryBox.takeout();
			break;
		}
	}
	return 0;
}
