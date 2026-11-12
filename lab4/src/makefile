
CC = gcc
CFLAGS = -I.

.PHONY: all clean

all: process_memory parallel_min_max parallel_sum

process_memory: process_memory.c
	$(CC) process_memory.c -o process_memory -no-pie

parallel_min_max: parallel_min_max.c utils.o find_min_max.o
	$(CC) -o parallel_min_max parallel_min_max.c utils.o find_min_max.o $(CFLAGS)

parallel_sum: parallel_sum.c sum.o utils.o
	$(CC) -o parallel_sum parallel_sum.c sum.o utils.o $(CFLAGS) -pthread

utils.o: utils.c utils.h
	$(CC) -c utils.c -o utils.o $(CFLAGS)

find_min_max.o: find_min_max.c utils.h find_min_max.h
	$(CC) -c find_min_max.c -o find_min_max.o $(CFLAGS)

sum.o: sum.c sum.h
	$(CC) -c sum.c -o sum.o $(CFLAGS)

clean:
	rm -f *.o process_memory sequential_min_max parallel_min_max parallel_sum
