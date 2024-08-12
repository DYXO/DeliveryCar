#ifndef __LINETRACK_H
#define __LINETRACK_H

#include <pigpio.h>
#include "motor.h"

class linetrack
{
public:
	/*
	 * Initialise the gpio
	 */
	linetrack();
	
	/*
	 * Terminate the gpio
	 */
	~linetrack();
	
	/*
	 * control the speed of the motor
	 * according to the retrun value
	 * of the infrared sensor
	 */
	void track_control(bool safe);
	
private:
	motor carmotor;
	int l_infraredgpio=23;
	int r_infraredgpio=22;
	bool l_value;
	bool r_value;
};

#endif
