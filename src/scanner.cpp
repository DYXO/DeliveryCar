#include "scanner.h"

scanner::scanner(int trig_gpio):scan_trig(trig_gpio)
{
	if(!gpioInitialise())
		printf("erro!gpio_init failed!\n");
	gpioSetMode(scan_trig, PI_OUTPUT);
	gpioWrite(scan_trig, 1); 
}

scanner::~scanner()
{
	
}

void scanner::startscan()
{
	if(running)
		return;
	running = 1;
	scanThread = std::thread(&scanner::scan,this);
}

void scanner::stopscan()
{
	if (!running) 
		return;
	running = 0;
	scanThread.join();
}

void scanner::scan()
{
	gpioWrite(scan_trig, 1); 
	gpioDelay(20);
	gpioWrite(scan_trig, 0); 
	while(1)
	{
		std::string barcode;
		barcode = Scan.receive();
		if (!barcode.empty()) 
		{
            gpioWrite(scan_trig, 1); 
			if(callback!=nullptr)
			{
				callback->scan_done(barcode);
			}
			gpioWrite(scan_trig, 1); 
            break;
        }
        time_sleep(1);
	}
}


void scanner::registerCallback(ScanDoneCallback* cb)
{
	callback=cb;
}

void scanner::unregisterCallback()
{
	callback=nullptr;
}
