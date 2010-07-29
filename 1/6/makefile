CFLAGS=-O0 -g -Wall -fpic
LDFLAGS=

all: hello

clean: 
	rm -f hello hello.o world.o main.o libhw.so

hello: libhw.so main.o
	gcc $(LDFLAGS) -o hello main.o -L. -lhw

hello.o: hello.c
	gcc -c $(CFLAGS) -o hello.o hello.c

world.o: world.c 
	gcc -c $(CFLAGS) -o world.o world.c
	
main.o: main.c 
	gcc -c $(CFLAGS) -o main.o main.c
	
libhw.so: hello.o world.o
	ld -dylib -o libhw.so hello.o world.o -lc