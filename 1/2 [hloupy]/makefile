CFLAGS=-O0 -g -Wall
LDFLAGS=

all: hello

clean: 
	rm -f main.o world.o hello.o

hello: main.o world.o hello.o
	gcc ${LDFLAGS} main.o world.o hello.o  -o hello

hello.o:
	gcc -c $(CDFLAGS) -o hello.o hello.c

world.o:
	gcc -c $(CDFLAGS) -o world.o world.c

main.o:
	gcc -c $(CDFLAGS) -o main.o main.c