#ifndef __SCANNER_H
#define __SCANNER_H

#include "serial.h"
#include <thread>  

class ScanDoneCallback {
public:
	/*
	 * Called when finished scan
	 */
	 virtual void scan_done(std::string data) = 0;
};

class scanner
{
public:
	scanner(int trig_gpio);
	~scanner();
	void registerCallback(ScanDoneCallback* cb);
	void unregisterCallback();
	void startscan();
	void stopscan();
private:
	SerialPort Scan;
	bool running=0;
	int scan_trig;
	void scan();
	std::thread scanThread;
	ScanDoneCallback* callback;
};



#endif
