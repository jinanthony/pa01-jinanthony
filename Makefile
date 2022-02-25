CXX = g++

BINARIES = game testbench tests

default: game testbench tests

game: cards.h cards.cpp main.cpp 
	g++ --std=c++11 -Wall cards.cpp main.cpp -o game

testbench: cards.h cards.cpp testbench.cpp
	g++ --std=c++11 -Wall cards.cpp testbench.cpp -o testbench

tests: cards.h cards.cpp tests.cpp
	g++ --std=c++11 -Wall cards.cpp tests.cpp -o tests

clean: 
	rm game testbench tests
