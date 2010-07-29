#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void ukonci() {
	srand(time(NULL));
	while((random()%500000000) != 1234){}
	printf("koncim!\n");
	kill(getppid(), SIGUSR1);
	exit(0);
}

int ukoncenych;
void handler(int s){
	++ukoncenych;
	//mel jsem tu printf, ale to neni reentrantni -> radsi nepouzivat
}

int main(int argc, char** argv) {
	ukoncenych=0;
	
	struct sigaction *sa;
	sa->sa_handler = handler;
	sigset_t sigset;
	sigemptyset(&sigset);
	sa->sa_mask = sigset;
	sa->sa_flags = SA_RESTART;
	
	sigaction(SIGUSR1, sa, NULL);
	
	if (! fork()) {
		ukonci();
	}
	if (! fork()) {
		ukonci();
	}
	
	while (ukoncenych<2) {}
	printf("megayay!\n");
	exit(1);
}		