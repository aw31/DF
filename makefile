CC_OPT = -Wall -O2

all: a analyze test

a: grid.o draw.o solution.cpp
	g++ $(CC_OPT) grid.o draw.o solution.cpp -o a

analyze: grid.o draw.o analyze.cpp
	g++ $(CC_OPT) grid.o draw.o analyze.cpp -o analyze

test: grid.o draw.o test.cpp
	g++ $(CC_OPT) grid.o draw.o test.cpp -o test

draw.o: stb_image_write.h draw.h grid.o draw.cpp
	g++ $(CC_OPT) -c grid.o draw.cpp -o draw.o

grid.o: grid.h grid.cpp
	g++ $(CC_OPT) -c grid.cpp -o grid.o

