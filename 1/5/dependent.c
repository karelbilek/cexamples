#include <stdio.h>

int main (int argc, char const *argv[])
{
	int system=0;
	
	#ifdef __APPLE__
		system=1;
	#endif
	
	#ifdef __LINUX__
		system=2;
	#endif
	
	if (system==1) {
		printf("MACOSXRLZ\n");
	} else if (system==2) {
		printf("LINUX is not bad either, but it's that funny\n");
	} else {
		printf("you got a weird system.");
	}
	
	return 0;
}