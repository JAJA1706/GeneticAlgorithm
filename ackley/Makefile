CC = g++
CFLAGS = -Wall -std=c++11 -lm

all: main.o ackley.o algorithm.o individual.o
	$(CC) $(CFLAGS) -o fun main.o ackley.o algorithm.o individual.o

individual.o: Individual.cpp Individual.hpp
	$(CC) $(CFLAGS) -c -o individual.o Individual.cpp

algorithm.o: algorithm.cpp algorithm.hpp
	$(CC) $(CFLAGS) -c -o algorithm.o algorithm.cpp

ackley.o: ackley.cpp ackley.hpp
	$(CC) $(CFLAGS) -c -o ackley.o ackley.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c -o main.o main.cpp

clean:
	rm -f *.o
