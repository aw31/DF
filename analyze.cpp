#include "grid.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
#include <sstream>
using namespace std;

const int D = 26;
int daynum, freq[1024] = {}, tot[1024] = {};
grid start[40], ans[40];

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

void mod3(int day){
	int freq[3] = {};
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++) freq[(i-j+3000)%3]+=ans[day](i,j);
	}
	cout << freq[0] << " " << freq[1] << " " << freq[2] << endl;
}

void check(int day){

	daynum = day;
	for(int i = 0; i<30; i++){
		for(int j = 0; j<30; j++){
			int stst = 0;
			for(int k = -1; k<2; k++){
				for(int l = -1; l<2; l++){
					stst = 2*stst+start[day](i+k,j+l);
				}
			}
			if((-daynum+3000)%3==(i-j+3000)%3){
				stst = 2*stst+1;
			} else if((-daynum+3000)%3==(i-j+3001)%3){
				stst*=2;
			} else continue;
			tot[stst]++;
			if(ans[day](i,j)) freq[stst]++;
		}
	}

}

int main(){

	for(int i = 1; i<=D; i++) load(i);

	for(int i = 1; i<=D; i++) mod3(i);

	/*
	freopen("solve7.txt", "w", stdout);
	for(int i = 2; i<=D; i+=2) check(i);
	for(int i = 0; i<1024; i++) cout << freq[i] << " " << tot[i] << '\n';
	*/

}
