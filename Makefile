CC=gcc -Wall
CFLAGS = -g -I/usr/include

all: main

main: main.o hdc1000.o
	$(CC) -o main -lwiringPi main.o hdc1000.o

main.o: main.c
	$(CC) -c main.c

hdc1000.o: hdc1000.c
	$(CC) -c hdc1000.c

clean:
	rm -f *~ *.o main

