CFLAGS = -pedantic -Wall --std=c++17 

all: driver

driver: main.o PriorityQueue.o ReadFile.o Transfer.o
	g++ main.o PriorityQueue.o ReadFile.o Transfer.o -o driver

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp 

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h
	g++ $(CFLAGS) -c PriorityQueue.cpp

ReadFile.o: ReadFile.cpp ReadFile.h
	g++ $(CFLAGS) -c ReadFile.cpp

Transfer.o: Transfer.cpp Transfer.h
	g++ $(CFLAGS) -c Transfer.cpp

clean:
	rm *.o driver