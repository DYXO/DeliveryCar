#include "motor.h"
#include "ultrasonic.h"

int main(int argc, char *argv[]) 
{
	ultrasonic test_ultrasonic;
	test_ultrasonic.echo_wait();
	return 0;
}
