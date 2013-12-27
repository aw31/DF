#include "grid.h"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

const int D = 25;
int daynum;

grid start[40], ans[40];
int freq[1024], tot[1024];

grid solve(grid g, double a1, double a2, double a3, double a4){

	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){

			double n_adj = 0;
			for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) if(k||l) n_adj+=g(i+k,j+l);
			if((-daynum+3000)%3==(i-j+3000)%3){
				if(n_adj==2) res(i, j)+=a1;
				else if(n_adj>=3) res(i,j)+=a2;
				if(g(i, j)) res(i, j)-=a3;
			} else if((-daynum+3000)%3==(i-j+3001)%3){
				if(n_adj==2) res(i,j)+=0.2;
				else if(n_adj>=3) res(i,j)+=0.3;
				if(g(i, j)) res(i, j)-=0.15;
			}

			int st = 0;
			for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) st = 2*st+g(i+k,j+l); 
			if((-daynum+3000)%3==(i-j+3000)%3) st = 2*st+1;
			else if((-daynum+3000)%3==(i-j+3001)%3) st*=2;
			else continue;
			if(tot[st]>a4) res(i,j) = 1.0*freq[st]/tot[st];

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
	for(int i = 21; i<=D; i++) res+=(check(i, a1, a2, a3, a4));
	return res/(D-20);
	//return res/((D+1)/2);

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

	ifstream fin("solve7.txt");
	for(int i = 0; i<1024; i++) fin >> freq[i] >> tot[i];

	double best = 0, bi, bj, bk, bl;
	for(double i = 0; i<1.01; i+=0.05){
		cout << i <<endl;
		for(double j = 0; j<1.01; j+=0.05){
			for(double k = 0; k<1.01; k+=0.05){
				for(int l = 0; l<10; l++){
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
