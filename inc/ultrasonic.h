#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include <stdio.h>
#include <pigpio.h>
#include <thread>  

class UltrasonicCallback {
public:
	/*
	 * Called when receive ehco.
	 */
	virtual void distance_ready(float dis) = 0;
};

class ultrasonic
{
public:
	ultrasonic();
	~ultrasonic();
	
	/*
	 * Registers the callback which is called 
	 * whenever distance is calculated
	 */
	void registerCallback(UltrasonicCallback* cb);
	
	/*
	 * Unregisters the callback to the callback interface.
	 */
	void unregisterCallback();
	
	void start();

private:
	bool running=0;
	int seconds;
	int last_seconds;
	int micros;
	int last_micros;
	int *p_s=&seconds;
	int *p_m=&micros;
	std::thread disThread;
	UltrasonicCallback* callback;
	float distance;
	void gpio_init();
	void wave_start();
	void echo_wait();
	const int triggpio=6;
	const int echogpio=5;
};

#endif
