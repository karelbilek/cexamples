#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <fcntl.h>
#include <errno.h>


typedef int bool;


int main (int argc, char *argv[])
{
	struct {
		bool in, out, rew;
		int n;
		char fin[250];
		char fout[250];
	} options;

	options.in=0;
	options.out=0;
	options.rew=0;
	options.n=0;
	
	int opt;
	
	while ((opt=getopt(argc, argv, "i:o:n:r"))!=-1){
		switch (opt) {
			case 'i': 
				options.in=1;
				strcpy(options.fin, optarg);
				break;
			case 'o':
				options.out=1;
				strcpy(options.fout, optarg);
				break;
			case 'n':
				options.n=atoi(optarg);
				break;
			case 'r':
				options.rew=1;
				break;
			case '?':
				fprintf(stderr, "usage: %s [-i infile] [-o outfile] [-n]\n", basename(argv[0]));
				return 1;
				break;
		}
	}
	
	int findes;
	if (options.in){
		findes = open(options.fin, O_RDONLY);
		if (findes==-1) {
			fprintf(stderr, "OMG fatal error! file %s fails to open for reading! errno=%d\n", options.fin, errno);
			return 1;
		}
	} else {
		findes = 0;
	}
	
	int foutdes;
	if (options.out) {
		int acc = access(options.fout, W_OK);
		if (acc==0) {
			//existuje, muzu psat
			if (options.rew) {
				foutdes = open(options.fout, O_WRONLY|O_TRUNC);
			} else {
				foutdes = open(options.fout, O_WRONLY|O_APPEND);
			}
		} else {
			
			if (errno == ENOENT) {
				
				//vse OK
				foutdes = open(options.fout, O_WRONLY|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
				printf("foutdes is %d!\n",foutdes);
			} else {
				fprintf(stderr, "OMG fatal error! file %s fails to open for writing! errno=%d\n", options.fout, errno);
				return 1;
			}
		}
		if (foutdes==-1){
			fprintf(stderr, "OMG fatal error! file %s fails to open for writing! errno=%d\n", options.fout, errno);
		}
	} else {
		foutdes=1;
	}
	
	
	int size = (options.n)?(options.n):512;
	char buf[size];
	
	int status=0; int tries=0;
	while (((status=read(findes, buf, size))>0) || ((status==-1) && (errno==EAGAIN) && (tries++<20))){
		if (status>0){
			write(foutdes, buf, status);
		}
	}
	
	
	if (options.in){
		close(findes);
	}
	if (options.out){
		close(foutdes);
	}
//	while 
	
	return 0;
}