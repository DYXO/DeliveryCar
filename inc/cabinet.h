#ifndef __CABINET_H
#define __CABINET_H

#include "scanner.h"
#include <thread>  

class cabinet
{
public:
	cabinet(scanner* s_point);
	~cabinet();
	void deposit();
	void takeout();
	
	/*
	 * the flag record the door
	 * is locked or not
	 */	
	bool lock=0;
	
	/*
	 * control the GPIO level to open
	 * the electromagnetic lock
	 */
	void Deposit_open();
	void Takeout_open();
	std::string password;
	
	bool scanbusy=0;
	
private:
	int scan_trig;
	scanner* s1;
	int lockfeedbackgpio=2;
	int lockcontrolgpio=3;
};

#endif
