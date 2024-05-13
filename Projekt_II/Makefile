CFLAGS = -pedantic -Wall --std=c++17 

all: prog

prog: main.o readFile.o mergeSort.o quickSort.o bucketSort.o functions.o
	g++ main.o readFile.o mergeSort.o  quickSort.o bucketSort.o functions.o -o prog

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp 

readFile.o: readFile.cpp
	g++ $(CFLAGS) -c readFile.cpp

mergeSort.o: mergeSort.cpp
	g++ $(CFLAGS) -c mergeSort.cpp

quickSort.o: quickSort.cpp
	g++ $(CFLAGS) -c quickSort.cpp

bucketSort.o: bucketSort.cpp
	g++ $(CFLAGS) -c bucketSort.cpp

functions.o: functions.cpp
	g++ $(CFLAGS) -c functions.cpp
clean:
	rm *.o prog