#include "grid.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
#include <sstream>
using namespace std;

const int D = 25;
int daynum, freq[1024] = {}, tot[1024] = {};

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

	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			int stst = 0;
			for(int k = -1; k<2; k++){
				for(int l = -1; l<2; l++){
					stst = 2*stst+start(i+k,j+l);
				}
			}
			if((-daynum+3000)%3==(i-j+3000)%3){
				stst = 2*stst+1;
			} else if((-daynum+3000)%3==(i-j+3001)%3){
				stst*=2;
			} else continue;
			tot[stst]++;
			if(ans(i,j)) freq[stst]++;
		}
	}

}

int main(){

	freopen("solve7.txt", "w", stdout);
	for(int i = 1; i<=20; i++) check(i);
	for(int i = 0; i<1024; i++) cout << freq[i] << " " << tot[i] << '\n';

}
