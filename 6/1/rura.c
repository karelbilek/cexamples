#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void produce(int pipe_des) {
	char my_char[10];
	int i;
	for (i=0; i<100; ++i){
		sprintf(my_char, "Num %d\n", i);
		write(pipe_des, my_char, 10*sizeof(char));
	}
	printf("ZHEBAVA PRODUCE!\n");
	close(pipe_des);
	exit(10);
}

void consume(int pipe_des) {
	char my_char[100];
	while (read(pipe_des, my_char, 100*sizeof(char))) {
		printf("ctu....\n");
		
		write(1, my_char, 100);
	}
	printf("ZHEBAVA CONSUME!\n");
	close(pipe_des);
	exit(20);
}

void wait_and_die(int first_child, int second_child) {
	int second_status;
	waitpid(second_child,&second_status, 0);
	printf("\n----2 dite skoncilo se statusem %d\n", WEXITSTATUS(second_status));
	int first_status;
	waitpid(first_child,&first_status, 0);
	printf("\n----1 dite skoncilo se statusem %d\n", WEXITSTATUS(first_status));
	exit(0);
}


int main (int argc, char *argv[])
{
	int pipe_descriptor[2];
	
	pipe(pipe_descriptor);
	
	int first_child;
	int second_child;
	
	switch (first_child=fork()){
		case 0: close(pipe_descriptor[0]); produce(pipe_descriptor[1]); break;
		case -1: fprintf(stderr, "What is this? :-("); return 1; break;
		default: 
			switch (second_child=fork()) {
				case 0: close(pipe_descriptor[1]); consume(pipe_descriptor[0]); break;
				case -1: fprintf(stderr, "What is this? :-(("); return 1; break;
				default: close(pipe_descriptor[1]); close(pipe_descriptor[0]); wait_and_die(first_child, second_child); break;
			}
		
	}
	return 0;
}


