#include "grid.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <sstream>
using namespace std;

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

	vector<pii> a = start.get_frogs(), b = ans.get_frogs();
	int mod3[3] = {};
	for(int i = 0; i<30; i++){
		for(int j = 0;j<30; j++){
			if(start(i,j)) mod3[(i-j+3000)%3]++;
		}
	}
	cout << daynum << " " << mod3[0] << " " << mod3[1] << " " << mod3[2] << endl;

}

int main(){

	int D = 18;
	for(int i = 1; i<=D; i++) check(i);

}
