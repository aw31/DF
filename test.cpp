#include "grid.h"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

const int D = 21;
int daynum;

grid start[40], ans[40];

grid solve(grid g, double a1, double a2, double a3, double a4){

	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			double n_adj = 0;
			for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) if(k||l) n_adj+=g(i+k,j+l);
			if((-daynum+3000)%3==(i-j+3000)%3){
				res(i, j)+=a1*n_adj;
				if(g(i, j)) res(i, j)-=a3;
			} else if((-daynum+3000)%3==(i-j+3001)%3){
				res(i, j)+=a2*n_adj;
				if(g(i, j)) res(i, j)-=a4;
			}
		}
	}
	res.fix();
	return res;

}

// returns the score of a solution on a given day
double check(int day, double a1, double a2, double a3, double a4){
	daynum = day;
	return score(ans[day], solve(start[day], a1, a2, a3, a4));
}

// returns average score of a solution
double check(double a1, double a2, double a3, double a4){

	double res = 0;
	for(int i = 1; i<=D; i++) res+=(check(i, a1, a2, a3, a4));
	return res/D;

}

// loads the data for a given day into start and ans
void load(int day){

	stringstream file;
	file << "data\\d" << (day<10?"0":"") << day << (day+1<10?"0":"") << day+1 << ".txt";
	freopen(file.str().c_str(), "r", stdin);
	string s[30];
	for(int i = 0; i<30; i++) cin >> s[i];
	grid st(s);
	for(int i = 0; i<30; i++) cin >> s[i];
	grid an(s);
	start[day] = st;
	ans[day] = an;

}

int main(){

	for(int i = 1; i<=D; i++) load(i);
	double best = 0, bi, bj, bk, bl;
	for(double i = 0; i<=0.5; i+=0.05){
		for(double j = 0; j<=0.5; j+=0.05){
			for(double k = 0; k<=0.5; k+=0.05){
				for(double l = 0; l<=0.5; l+=0.05){
					double s = check(i,j,k,l);
					if(s>best){
						best = s;
						bi = i;
						bj = j;
						bk = k;
						bl = l;
					}
				}
			}
		}
	}
	cout << best << " " << bi << " " << bj << " " << bk << " " << bl << endl;

}
