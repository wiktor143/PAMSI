CPPFLAGS = -pedantic -Wall --std=c++17 

all: prog

prog: main.o checkersBoard.o piece.o gameController.o
	g++ main.o checkersBoard.o piece.o gameController.o -o prog

main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp 

checkersBoard.o: checkersBoard.cpp
	g++ $(CPPFLAGS) -c checkersBoard.cpp

piece.o: piece.cpp
	g++ $(CPPFLAGS) -c piece.cpp

gameController.o: gameController.cpp
	g++ $(CPPFLAGS) -c gameController.cpp
clean:
	rm *.o prog