#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

const double eps = 1e-9;

int daynum;

struct grid{
	double a[32][32];
	grid(){memset(a, 0, sizeof(a));}
	grid(string arr[]){
		for(int i = 0; i<30; i++) for(int j = 0; j<arr[i].size(); j+=2) a[i+1][j/2+1] = (arr[i][j]=='1');
	}
	double operator()(int x, int y) const {return a[x+1][y+1];}
	double& operator()(int x, int y){return a[x+1][y+1];}

};

vector<pii> get_frogs(grid g){
	vector<pii> res;
	for(int i = 0; i<30; i++) for(int j = 0; j<30; j++) if(abs(g(i, j)-1)<eps) res.push_back(pii(i, j));
	return res;
}

typedef grid (*solve_func) (grid g);

ostream& operator<<(ostream &o, grid g){
	for(int i = 0; i<30; i++){
		for(int j = 0; j<29; j++) o << g(i,j) << ',';
		o << g(i,29) << '\n';
	}
	return o;
}

const double min_score = -1000;

double score(grid a, grid b){
	double s = 0;
	for(int i = 0; i<30; i++) for(int j = 0; j<30; j++) s+=(a(i,j)-b(i,j))*(a(i,j)-b(i,j));
	double k = max(min_score, 20-sqrt(s));
	return k*k*(2*(k>0)-1)/4;
}

grid solve0(grid g){
	// sets everything to 1/9
	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++) res(i,j) = 1/9.;
	}
	return res;
}

grid solve1(grid g){
	// for each cell, increments all neighboring cells by 1/8
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
	return res;
}

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
	return res;
}

grid solve3(grid g){
	grid res;
	//cout << daynum << endl;
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 30; j++){
			if(((j-i+3000)% 3) == ((daynum) % 3)){
				res(i,j) = 0.25;
			} else if(((j-i+3000)% 3) == ((daynum+1) % 3)){
				res(i,j) = 0.083333;
			}
		}
	}
	return res;
}

grid solve4(grid g){
	// for each cell, increments all neighboring cells by 1/8
	// with daynum and x-y mod 3 observation
	// with observation that a frog square is less likely to be filled next turn
	grid res;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			if(abs(g(i,j)-1)<eps){
				res(i,j)-=0.2;
				for(int k = -1; k<2; k++){
					for(int l = -1; l<2; l++){
						if(k!=0||l!=0){
							if((-daynum+3000)%3==(i+k-j-l+3000)%3) res(i+k, j+l)+=0.3;
							else if((-daynum+3000)%3==(i+k-j-l+3001)%3) res(i+k, j+l)+=0.1;
						}
					}
				}
			}
		}
	}
	for(int i = 0; i<30; i++) for(int j = 0; j<30; j++) res(i, j) = max(min(res(i, j), 1.), 0.);
	return res;
}

const int n_sol = 5;
solve_func sol[n_sol] = {solve0, solve1, solve2, solve3, solve4};

grid solve(grid g, int k){
	return sol[k](g);
}

// need to finish!
vector<int> find_map(vector<pii> a, vector<pii> b){
	vector<int> res;
	for(int i = 0; i<30; i++) res.push_back(i);
	return res;
}

vector<double> check(int day){

	stringstream file;
	file << "data\\d" << (day<10?"0":"") << day << (day+1<10?"0":"") << day+1 << ".txt";
	freopen(file.str().c_str(), "r", stdin);
	string s[30];
	for(int i = 0; i<30; i++) cin >> s[i];
	grid start(s);
	for(int i = 0; i<30; i++) cin >> s[i];
	grid ans(s);
	cin >> daynum;

	vector<double> res;
	for(int i = 0; i<n_sol; i++) res.push_back(score(ans, solve(start, i)));
	return res;

}

int main(){

	// input is day N and day N+1
	double avg[n_sol] = {};
	int D = 18;
	for(int i = 1; i<=D; i++){
		vector<double> v = check(i);
		for(int j = 0; j<n_sol; j++) avg[j]+=v[j]/D;
	}
	for(int i = 0; i<n_sol; i++) cout << avg[i] << " ";
	cout << endl;

}

