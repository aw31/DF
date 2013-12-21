#include <string>
#include <utility>
#include <vector>

#ifndef __GRID_H_INCLUDED__
#define __GRID_H_INCLUDED__

typedef std::pair<int,int> pii;

struct grid{
	double a[32][32];
	grid();
	grid(std::string[]);
	double& operator()(int, int);
	void fix();
	std::vector<pii> get_frogs();
};

std::ostream& operator<<(std::ostream, grid);
double score(grid, grid);

#endif
