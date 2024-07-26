#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include <stdio.h>
#include <pigpio.h>

class ultrasonic
{
public:
	ultrasonic();
	~ultrasonic();
	float echo_wait();
private:
	int seconds;
	int last_seconds;
	int micros;
	int last_micros;
	int *p_s=&seconds;
	int *p_m=&micros;
	float distance;
	void gpio_init();
	void wave_start();
	const int triggpio=6;
	const int echogpio=5;
};

#endif
