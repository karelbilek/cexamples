
#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char** argv) {
	void *handle;
	
	handle = dlopen("libm.so", RTLD_NOW);
	if (handle==NULL) {
		printf("DIE");
		return 1;
	}
	
	int (* funct)(int);
	funct = dlsym(handle, "factorial");
	
	char *err;
	if ((err=dlerror())!=NULL) {
		printf("SHIT! %s", err);
		return 1;
	}
	
	int lol = funct(50);
	
	printf("WATPORT%d",lol);
	
	dlclose(handle);
	return 0;
}		