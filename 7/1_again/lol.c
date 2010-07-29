#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("chyba - malo parametru!\n");
		exit(1);
	}
	
	int fildes = open(argv[1], O_RDWR);
	if (fildes<0) {
		printf("chyba errno %d pri otevirani souboru %s!\n", errno, argv[1]);
		exit(1);
	}
	
	int filsize = lseek(fildes, 0, SEEK_END);
	
	if (filsize<=0) {
		printf("What the hell, maaan, soubor %s je velkej %d, I don like dat\n", argv[1], filsize);
		exit(1);
	}
	
	char* byty = mmap(NULL, filsize, PROT_READ|PROT_WRITE, MAP_SHARED, fildes, 0);
	
	int i;
	for (i = 0; i < filsize; ++i) {
		switch (byty[i]) {
			case '.': byty[i]='X'; break;
			//case 'X': byty[i]='.'; break;
			default: break;
		}
	}
	
	munmap(byty, filsize);
	
	close(fildes);
	exit(0);
}		