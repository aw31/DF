#include "grid.h"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

grid::grid(){memset(a, 0, sizeof(a));}
grid::grid(string arr[]){
	for(int i = 0; i<30; i++){
		for(int j = 0; j<arr[i].size(); j+=2) a[i+1][j/2+1] = (arr[i][j]=='1');
	}
}
double& grid::operator()(int x, int y){return a[x+1][y+1];}
void grid::fix(){
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++) (*this)(i,j) = max(min((*this)(i,j), 1.), 0.);
	}
}


vector<pii> grid::get_frogs(){
	vector<pii> res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			if((*this)(i, j)) res.push_back(pii(i, j));
		}
	}
	return res;
}

double min_score = 0;

double score(grid a, grid b){
	double s = 0;
	for(int i = 0; i<30; i++) for(int j = 0; j<30; j++) s+=(a(i,j)-b(i,j))*(a(i,j)-b(i,j));
	double k = max(min_score, 20-sqrt(s));
	return k*k/4;
}
