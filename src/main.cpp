#include "motor.h"

int main(int argc, char *argv[]) 
{
	motor testmotor;
	testmotor.set_speed(200,0);
	testmotor.set_speed(0,-200);
	testmotor.set_speed(60,60);
	time_sleep(2);
	testmotor.set_speed(-60,-60);
	time_sleep(2);
	return 0;
}
