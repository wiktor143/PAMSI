CFLAGS = -pedantic -Wall --std=c++17 

all: prog

prog: driver.o PriorityQueue.o ReadFile.o Transfer.o
	g++ driver.o PriorityQueue.o ReadFile.o Transfer.o -o prog

driver.o: driver.cpp
	g++ $(CFLAGS) -c driver.cpp 

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h
	g++ $(CFLAGS) -c PriorityQueue.cpp

ReadFile.o: ReadFile.cpp ReadFile.h
	g++ $(CFLAGS) -c ReadFile.cpp

Transfer.o: Transfer.cpp Transfer.h
	g++ $(CFLAGS) -c Transfer.cpp

clean:
	rm *.o prog