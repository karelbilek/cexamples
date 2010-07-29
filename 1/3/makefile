CFLAGS=-O0 -g -Wall
LDFLAGS=

all: hello

clean: 
	rm -f main.o world.o hello.o libhello.a

hello: main.o libhello.a
	gcc ${LDFLAGS} main.o  -o hello -L. -lhello

hello.o:
	gcc -c $(CDFLAGS) -o hello.o hello.c

world.o:
	gcc -c $(CDFLAGS) -o world.o world.c

libhello.a: hello.o world.o
	ar -rcs libhello.a hello.o world.o
