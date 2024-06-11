CPPFLAGS = -pedantic -Wall --std=c++17 

all: prog

prog: main.o checkersBoard.o field.o gameController.o inputArgsChecker.o player.o
	g++ main.o checkersBoard.o field.o gameController.o inputArgsChecker.o player.o -o prog

main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp 

checkersBoard.o: checkersBoard.cpp
	g++ $(CPPFLAGS) -c checkersBoard.cpp

field.o: field.cpp
	g++ $(CPPFLAGS) -c field.cpp

gameController.o: gameController.cpp
	g++ $(CPPFLAGS) -c gameController.cpp

inputArgsChecker.o: inputArgsChecker.cpp
	g++ $(CPPFLAGS) -c inputArgsChecker.cpp

player.o: player.cpp
	g++ $(CPPFLAGS) -c player.cpp
	
clean:
	rm *.o prog