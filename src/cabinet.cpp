#include "cabinet.h"

class depositCallback:public ScanDoneCallback
{
public:
	cabinet* box;
	depositCallback(cabinet* box_p)
	{
		box=box_p;
	}
private:
	virtual void scan_done(std::string data) 
	{
		if(box->lock==1)
		{
			box->scanbusy=0;
			return;
		}
		else
		{
			box->password.clear();
			box->password=data;
			box->Deposit_open();
		}
		box->scanbusy=0;
	}
};

class takeoutCallback:public ScanDoneCallback
{
public:
	cabinet* box;
	takeoutCallback(cabinet* box_p)
	{
		box=box_p;
	}
private:
	virtual void scan_done(std::string data) 
	{
		if(box->lock==0)
		{
			box->scanbusy=0;
			printf("no save things!\n");
			return;
		}
		else
		{
			if(box->password==data)
			{
				printf("code right!\n");
				box->password.clear();
				box->Takeout_open();
			}
			else
			{
				printf("erro code!\n");
			}
		}
		box->scanbusy=0;
	}
};

cabinet::cabinet(scanner* s_point)
{
	s1=s_point;
}

cabinet::~cabinet()
{
	
}

void cabinet::deposit()
{
	if(scanbusy==1)
	{
		printf("scanner busy\n");
		return;
	}
	depositCallback depositcallback(this);
	s1->registerCallback(&depositcallback);
	scanbusy=1;
	s1->startscan();
	s1->stopscan();
}

void cabinet::takeout()
{
	if(scanbusy==1)
	{
		printf("scanner busy\n");
		return;
	}
	takeoutCallback takeoutcallback(this);
	s1->registerCallback(&takeoutcallback);
	scanbusy=1;
	s1->startscan();
	s1->stopscan();
}

void cabinet::Deposit_open()
{
	lock=0;
	printf("box opened!\n");
	/*
	 * high level for 1 sec  
	 * to open the lock
	 */
	gpioWrite(lockcontrolgpio, 1);
	time_sleep(1);
	gpioWrite(lockcontrolgpio, 0);
	time_sleep(1);
	time_sleep(1);
	time_sleep(1);
	time_sleep(1);
	time_sleep(1);
	lock=gpioRead(lockfeedbackgpio);
	//******test
	//lock=1;
	//******
	if(lock==1)
	{
		printf("deposit sucess!\n");
	}
	else
	{
		printf("didn't close, fail!\n");
		password.clear();
	}
}

void cabinet::Takeout_open()
{
	lock=0;
	printf("box opened!\n");
	/*
	 * high level for 1 sec  
	 * to open the lock
	 */
	gpioWrite(lockcontrolgpio, 1);
	time_sleep(1);
	gpioWrite(lockcontrolgpio, 0);
}
