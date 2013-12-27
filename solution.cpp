#include "grid.h"
#include "draw.h"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

typedef pair<int,int> pii;
typedef grid (*solve_func) (grid g);

const double eps = 1e-9;
const int D = 26;

int daynum;

ostream& operator<<(ostream &o, grid g){
	for(int i = 0; i<30; i++){
		for(int j = 0; j<29; j++) o << (g(i,j)) << ',';
		o << g(i,29) << '\n';
	}
	return o;
}

// sets everything to 1/9
// 27.94
grid solve0(grid g){
	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++) res(i,j) = 1/9.;
	}
	res.fix();
	return res;
}

// for each cell, increments all neighboring cells by 1/8
// 35.96
grid solve1(grid g){
	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			if(g(i,j)){
				for(int k = -1; k<2; k++){
					for(int l = -1; l<2; l++){
						if(k!=0||l!=0) res(i+k,j+l)+=1/8.;
					}
				}
			}
		}
	}
	res.fix();
	return res;
}

// for each cell, increments all side-adjacent cells by 1/4 
// 34.23
grid solve2(grid g){
	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			if(g(i,j)){
				int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
				for(int k = 0; k<4; k++) res(i+dx[k], j+dy[k])+=1/4.;
			}
		}
	}
	res.fix();
	return res;
}

// fail
// 30.77
grid solve3(grid g){
	grid res;
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30; j++){
			if(((j-i+3000)% 3) == ((daynum) % 3)){
				res(i,j) = 0.25;
			} else if(((j-i+3000)% 3) == ((daynum+1) % 3)){
				res(i,j) = 0.083333;
			}
		}
	}
	res.fix();
	return res;
}

// for each cell, increments all neighboring cells
// with daynum and x-y mod 3 observation
// with observation that a frog square is less likely to be filled next turn
// 48.80
grid solve4(grid g){
	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			double n_adj = 0;
			for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) if(k||l) n_adj+=g(i+k,j+l);
			if((-daynum+3000)%3==(i-j+3000)%3){
				res(i, j)+=0.35*n_adj;
				if(g(i,j)) res(i,j)-=0.3;
			}
			else if((-daynum+3000)%3==(i-j+3001)%3){
				res(i, j)+=0.1*n_adj;
				if(g(i,j)) res(i,j)-=0.1;
			}
		}
	}
	res.fix();
	return res;
}

// adds 1/3 to all moves that keep x-y mod 3 good
// 43.76
grid solve5(grid g){
	grid res;
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30; j++){
			if(g(i,j)){
				res(i-1, j) += 0.33333;
				res(i, j+1) += 0.33333;
				res(i+1, j-1) += 0.33333;
			}
		}
	}
	res.fix();
	return res;
}

// reweighting of solve4, performs better
// 52.88
grid solve6(grid g){
	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			int n_adj = 0;
			for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) if(k||l) n_adj+=g(i+k,j+l)+eps;
			if((-daynum+3000)%3==(i-j+3000)%3){
				if(n_adj==2) res(i, j) = 0.85-g(i,j)*0.4;
				else if(n_adj>=3) res(i,j) = 0.95-g(i,j)*0.5;
			} else if((-daynum+3000)%3==(i-j+3001)%3){
				if(n_adj==2) res(i, j) = 0.2-g(i,j)*0.2;
				else if(n_adj>=3) res(i,j) = 0.3-g(i,j)*0.3;
			}
		}
	}
	res.fix();
	return res;
}

int freq_7[1024], tot_7[1024];

// if we have >4 data points about a state, computes probability that it is white
// otherwise, uses solve6
grid solve7(grid g){

	grid res, s6 = solve6(g);
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){

			int st = 0;
			for(int k = -1; k<2; k++) for(int l = -1; l<2; l++) st = 2*st+g(i+k,j+l); 
			if((-daynum+3000)%3==(i-j+3000)%3) st = 2*st+1;
			else if((-daynum+3000)%3==(i-j+3001)%3) st*=2;
			else continue;

			if(tot_7[st]>4){
				res(i,j) = 1.0*freq_7[st]/tot_7[st];
			} else {
				res(i,j) = s6(i,j);
			}
		}
	}
	res.fix();
	return res;

}


const int n_sol = 8;
solve_func sol[n_sol] = {solve0, solve1, solve2, solve3, solve4, solve5, solve6, solve7};

grid start[40], ans[40];

grid solve(grid g, int k){
	return sol[k](g);
}

grid get_next(int day, int k){
	daynum = day+1;
	return solve(ans[day], k);
}

// returns the score of a solution on a given day
double check(int day, int sol_num){
	daynum = day;
	return score(ans[day], solve(start[day], sol_num));
}

// returns average score of a solution
double check(int sol_num){

	double res = 0;
	//for(int i = 1; i<=D; i++) res+=(check(i, sol_num));
	//return res/D;
	for(int i = 1; i<=D; i+=2) res+=(check(i, sol_num));
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

// does preprocessing for all solve functions
void preprocess(){

	// solve7
	ifstream fin("solve7.txt");
	for(int i = 0; i<1024; i++) fin >> freq_7[i] >> tot_7[i];
	fin.close();

}

int main(){

	for(int i = 1; i<=D; i++) load(i);
	preprocess();

	double avg[n_sol] = {};
	int best = 0;
	for(int i = 0; i<n_sol; i++){
		avg[i] = check(i);
		if(avg[i]>avg[best]) best = i;
	}
	for(int i = 0; i<n_sol; i++) cout << avg[i] << " ";
	cout << endl << endl;

	cout << "best solve: " << best << endl;
	cout << endl;

	// a star indicates that the day was used in the training set
	cout << "recent scores: " << endl;
	for(int i = D-9; i<=D; i++) cout << "    " << check(i, best) << (i%2?"":"*") << endl;
	cout << endl;

	cout << "today's submission: " << endl;
	cout << fixed << setprecision(3) << get_next(D, best) << endl;
	cout << endl;

	for(int i = 1; i<=D; i++){
		stringstream image_name;
		image_name << "images\\" << i << ".png";
		draw(get_next(i, best), image_name.str());
	}

}

