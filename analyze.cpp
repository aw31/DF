#include "grid.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
#include <sstream>
using namespace std;

int daynum, freq[131072] = {}, tot[131072] = {};

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
			for(int k = -2; k<2; k++){
				for(int l = -2; l<2; l++){
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

	freopen("solve7-1.txt", "w", stdout);
	int D = 23;
	for(int i = 2; i<=D; i+=2) check(i);
	for(int i = 0; i<131072; i++) cout << freq[i] << " " << tot[i] << '\n';

}
