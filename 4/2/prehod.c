#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/uio.h>
#include <sys/types.h>


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
				fprintf(stderr, "usage: %s [-i infile] [-o outfile] [-n size] [-r]\n", basename(argv[0]));
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
	
	int iovecsize=20;
	int to_read_size=20;
	int to_write_size=0;
	
	int i;
	struct iovec *iov=(struct iovec *)malloc(iovecsize * sizeof(struct iovec));
	struct iovec *to_read_iov = iov;
	
	for (i=0; i<iovecsize; ++i) {
		(iov[i]).iov_len = size;
		(iov[i]).iov_base = (char *)malloc(size * sizeof (char));
	}
	
	int status=0; int tries=0;
	while (((status=readv(findes, to_read_iov, to_read_size))>0) || ((status==-1) && (errno==EAGAIN) && (tries++<20))){
		if (status==size*to_read_size) {
			//pokud se jeste da cist, musi se neco delat!
			struct iovec* another = (struct iovec *)malloc(iovecsize *2* sizeof(struct iovec));
			for (i=0; i<iovecsize; ++i){
				another[i]=iov[i];
			}
			for (i=iovecsize; i<2*iovecsize;++i){
				(another[i]).iov_len = size;
				(another[i]).iov_base = (char *)malloc(size * sizeof (char));
			}
			to_read_size = iovecsize;
			to_read_iov = &(another[iovecsize]);
			iovecsize*=2;
			free(iov);
			iov=another;
		}
		if (status>0) {
			to_write_size+=status/size;
		}
	}
	
	struct iovec *to_write_iov=(struct iovec *)malloc(to_write_size * sizeof(struct iovec));
	for (i=0;i<to_write_size; ++i){
		to_write_iov[i]=iov[to_write_size-i-1];
		printf("wtf to_write_iov[%d].iov_base = %s\n", i, to_write_iov[i].iov_base);
		printf("wtf to_write_iov[%d].size = %d\n", i, to_write_iov[i].iov_len);
		
	}

	status = writev(foutdes,to_write_iov, to_write_size);
	if (status==-1) {
		printf("maxiov=%d, jamam = %d\n",UIO_MAXIOV,to_write_size);
	}
	
	//na free() pecu, nechce se mi to delat a stejne se to ted uvolni samo
	
	
	
	if (options.in){
		close(findes);
	}
	if (options.out){
		close(foutdes);
	}
//	while 
	
	return 0;
}