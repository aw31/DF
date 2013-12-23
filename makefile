CC_OPT = -Wall -O2

all: a analyze test

a: grid.h grid.o solution.cpp
	g++ $(CC_OPT) grid.o solution.cpp -o a

analyze: grid.h grid.o analyze.cpp
	g++ $(CC_OPT) grid.o analyze.cpp -o analyze

test: grid.h grid.o test.cpp
	g++ $(CC_OPT) grid.o test.cpp -o test

grid.o: grid.h grid.cpp
	g++ $(CC_OPT) -c grid.cpp -o grid.o
