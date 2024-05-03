CFLAGS = -pedantic -Wall --std=c++17 

all: prog

prog: main.o
	g++ main.o -o prog

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp 

clean:
	rm *.o prog