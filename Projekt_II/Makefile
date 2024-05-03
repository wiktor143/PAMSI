CFLAGS = -pedantic -Wall --std=c++17 

all: prog

prog: main.o readFile.o
	g++ main.o readFile.o -o prog

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp 

readFile.o: readFile.cpp
	g++ $(CFLAGS) -c readFile.cpp

clean:
	rm *.o prog