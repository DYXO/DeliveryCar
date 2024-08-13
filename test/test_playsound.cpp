#include "playsound.h"


int main(int argc, char *argv[]) 
{
	soundplayer test("Sound.wav");
	test.play();
	while(1);
	return 0;
}
