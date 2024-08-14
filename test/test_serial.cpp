#include "serial.h"


int main(int argc, char *argv[]) 
{
	SerialPort serial;
	serial.send("hello!\n");
	while(1)
	{
		std::string data;
		data = serial.receive();
		std::cout<<data<<std::endl;
		time_sleep(1);
	}
	return 0;
}
