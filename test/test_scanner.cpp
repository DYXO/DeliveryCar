#include "scanner.h"

class PrintBarCodeCallback:public ScanDoneCallback
{
	virtual void scan_done(std::string data) 
	{
		std::cout<<data<<std::endl;
	}
};

int main(int argc, char *argv[]) 
{
	/*if(!gpioInitialise())
	{
		printf("erro!gpio_init failed!\n");
	}*/
	scanner s1(16);
	PrintBarCodeCallback printBarCode;
	s1.registerCallback(&printBarCode);
	s1.startscan();
	s1.stopscan();
	while(1)
	{

	}
	return 0;
}
