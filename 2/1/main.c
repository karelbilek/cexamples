#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main (int argc, char const *argv[])
{
	if (argc < 2) {
		printf("not enough arguments (you gave me %d)\n", argc-1);
		return 1;
	}
	const char *file_name = argv[1];
	
	int file_des;
	if ((file_des = open(file_name, O_RDONLY)) == -1) {
		printf("Error opening the file %s\n",file_name);
		return 1;
	}
	
	char *read_buffer = malloc(1000 * sizeof(char));
	
	int read_count;
	while ((read_count = read(file_des, read_buffer, 1000))) {
		int i;
		for (i=0; i<read_count; i++) {
			char to_print = read_buffer[i];
			if ((to_print<='z')&&(to_print>='a')){
				to_print+='A'-'a';
			}
			printf("%c", to_print);
		}
	}
	
	free(read_buffer);
	
	return 0;
}


