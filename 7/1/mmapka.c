#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>


int main (int argc, char *argv[])
{
	int fildes=open("obr.jpeg", O_RDWR);
	

	int filsize = lseek(fildes, 0, SEEK_END);
	printf("filsize? %d!\n",filsize);
		
	char *p=mmap (0, filsize, PROT_READ|PROT_WRITE, MAP_SHARED, fildes, 0);
	
	int i;
	for (i=0; i<filsize; ++i) {
		if (p[i]==':') {
			p[i]='X';
		}
	}
	
	munmap(p, filsize);
	
	return 0;
}