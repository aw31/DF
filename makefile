CC_OPT = -Wall -O2

a: grid.h solution.cpp solution.cpp
	g++ $(CC_OPT) grid.cpp solution.cpp -o a
