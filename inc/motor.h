#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdio.h>
#include <pigpio.h>

class motor
{
public:
	/*
	 * Initialise the gpio
	 */
	motor();
	
	/*
	 * Terminate the gpio
	 */
	~motor();
	
	/* set the speed of the motor
	 * input number from -100 to 100
	 * minus means the motor rotates
	 * in the opposite driection
	 */
	void set_speed(float leftspeed,float rightspeed);
	
	/*
	 * stop all the motor by setting PWM to 0
	 */
	void stop();
	
private:
	// GPIO Initialise sucess or not
    bool initstate=false; 
    /*
     * set pwm on l_motorgpio1 and l_motorgpio2 
     * to control the speed of the left side motors
     * same to the right side
     */
	const int l_motorgpio1 = 17;
	const int l_motorgpio2 = 25;
	const int r_motorgpio1 = 27;
	const int r_motorgpio2 = 24;
};

#endif
