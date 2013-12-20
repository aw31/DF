#include <iostream>
#include <cstring>
#include <cstdio>
#include <sstream>
using namespace std;

struct grid{
	double a[32][32];
	grid(){memset(a, 0, sizeof(a));}
	grid(string arr[]){
		for(int i = 0; i<30; i++) for(int j = 0; j<arr[i].size(); j+=2) a[i+1][j/2+1] = (arr[i][j]=='1');
	}
	double operator()(int x, int y) const {return a[x+1][y+1];}
	double& operator()(int x, int y){return a[x+1][y+1];}

};

int daynum;

void check(int day){

	stringstream file;
	file << "data\\d" << (day<10?"0":"") << day << (day+1<10?"0":"") << day+1 << ".txt";
	freopen(file.str().c_str(), "r", stdin);
	string s[30];
	for(int i = 0; i<30; i++) cin >> s[i];
	grid start(s);
	for(int i = 0; i<30; i++) cin >> s[i];
	grid ans(s);
	cin >> daynum;

	int c[2] = {};
	for(int i = 0; i<30; i++){
		for(int j = 0;j<30; j++){
			c[(int)start(i,j)]+=(int)ans(i,j);
		}
	}
	cout << c[0]/800. << " " << c[1]/100. << endl;

}

int main(){

	int D = 18;
	for(int i = 1; i<=D; i++) check(i);

}
