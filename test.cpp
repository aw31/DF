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

const double eps = 1e-9;
const int D = 28;
int daynum;

grid start[40], ans[40];
int freq_7[1024], tot_7[1024];

// reweighting of solve4, performs better
// 52.88
grid solve6(grid g){
	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			int n_adj = 0;
			for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) if(k||l) n_adj+=g(i+k,j+l)+eps;
			if((-daynum+3000)%3==(i-j+3000)%3){
				if(n_adj==2) res(i, j) = 0.9-g(i,j)*0.45;
				else if(n_adj>=3) res(i,j) = 0.95-g(i,j)*0.45;
			} else if((-daynum+3000)%3==(i-j+3001)%3){
				if(n_adj==2) res(i, j) = 0.2-g(i,j)*0.15;
				else if(n_adj>=3) res(i,j) = 0.3-g(i,j)*-0.2;
			}
		}
	}
	res.fix();
	return res;
}

grid solve7(grid g){

	grid res, s6 = solve6(g);
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){

			int st = 0;
			for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) st = 2*st+g(i+k,j+l); 
			if((-daynum+3000)%3==(i-j+3000)%3) st = 2*st+1;
			else if((-daynum+3000)%3==(i-j+3001)%3) st*=2;
			else continue;

			if(tot_7[st]>9){
				res(i,j) = 1.0*freq_7[st]/tot_7[st];
			} else {
				res(i,j) = s6(i,j);
			}
		}
	}
	res.fix();
	return res;

}

grid solve(grid g, double a1, double a2, double a3, double a4){

	double arr[] = {0, 0.3, 0.8, 0.9, 0.5, 0.15};
	grid res, adj, s7 = solve7(g);
	for(int i = 0; i<30; i++) for(int j = 0; j<30; j++){
		for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) adj(i,j)+=g(i+k,j+l);
	}
	for(int i = 0; i<30; i++) for(int j = 0; j<30; j++){
		if(!g(i,j)) continue;
		double p = 1;
		for(int k = -1; k<2; k++) for(int l = -1; l<2; l++){
			if((-daynum+3000)%3==(i+k-j-l+3000)%3){
				p*=(1-arr[(int)adj(i+k,j+l)]);
			}
		}
		if(abs(p)>1) continue;
		int alt = 0;
		for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) if((-daynum+3000)%3==(i+k-j-l+3001)%3) alt++;
		for(int k = -1; k<2; k++) for(int l = -1; l<2; l++){
			if((-daynum+3000)%3==(i+k-j-l+3001)%3) s7(i+k,j+l)+=p/alt/a1;
		}
	}
	return s7;

}

// returns the score of a solution on a given day
double check(int day, double a1, double a2, double a3, double a4){
	daynum = day;
	return score(ans[day], solve(start[day], a1, a2, a3, a4));
}

// returns average score of a solution
double check(double a1, double a2, double a3, double a4){

	double res = 0;
	for(int i = 1; i<=D; i+=2) res+=(check(i, a1, a2, a3, a4));
	return res/((D+1)/2);

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

	ifstream fin("solve7.txt");
	for(int i = 0; i<1024; i++) fin >> freq_7[i] >> tot_7[i];
	fin.close();

	for(int i = 1; i<=D; i++) load(i);
	double best = 0, bi, bj, bk, bl;
	for(double i = 1.0; i<=100.01; i+=10.0){
		cout << i << endl;
		for(double j = 0.0; j<=1.01; j+=0.05){
			for(double k = 0.0; k<=0.01; k+=0.05){
				for(double l = 0.0; l<=0.01; l+=0.05){
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
