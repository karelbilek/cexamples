#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void produce(int pipe_des) {
	close(1);
	dup(pipe_des);
	int i;
	for (i=0; i<100; ++i){
		printf("Num %d\n", i);
	}
	close(pipe_des);
	exit(10);
}

void consume(int pipe_des) {
	close(0);
	dup(pipe_des);
	char my_char[20];
	while (fgets(my_char, 20, stdin)) {
		printf("%s", my_char);
	}
	close(pipe_des);
	exit(20);
}

void wait_and_die(int first_child, int second_child) {
	int second_status;
	waitpid(second_child,&second_status, 0);
	printf("\n----2 dite skoncilo se statusem %d------\n", WEXITSTATUS(second_status));
	
	int first_status;
	waitpid(first_child,&first_status, 0);
	printf("\n----1 dite skoncilo se statusem %d------\n", WEXITSTATUS(first_status));
	exit(0);
}


int main (int argc, char *argv[])
{
	int socket_descriptor[2];
	
	socketpair(PF_LOCAL, SOCK_STREAM, 0, socket_descriptor);
	
	int first_child;
	int second_child;
	
	switch (first_child=fork()){
		case 0: close(socket_descriptor[0]); produce(socket_descriptor[1]); break;
		case -1: fprintf(stderr, "What is this? :-("); return 1; break;
		default: 
			switch (second_child=fork()) {
				case 0: close(socket_descriptor[1]); consume(socket_descriptor[0]); break;
				case -1: fprintf(stderr, "What is this? :-(("); return 1; break;
				default: close(socket_descriptor[1]); close(socket_descriptor[0]); wait_and_die(first_child, second_child); break;
			}
		
	}
	return 0;
}


