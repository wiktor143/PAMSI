CFLAGS = -pedantic -Wall --std=c++17 

all: driver

driver: main.o PriorityQueue.o
	g++ main.o PriorityQueue.o -o driver

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp 

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h
	g++ $(CFLAGS)-c PriorityQueue.cpp

clean:
	rm *.o driver