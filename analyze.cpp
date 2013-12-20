#include <iostream>
#include <cstring>
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

int main(){

	string s[30];
	for(int i = 0; i<30; i++) cin >> s[i];
	grid start(s);
	for(int i = 0; i<30; i++) cin >> s[i];
	grid ans(s);
	cin >> daynum;
	int mod[3] = {};
	for(int i = 0; i<30; i++) for(int j = 0; j<30; j++) if(start(i,j)) mod[(i-j+3000)%3]++;
	for(int i = 0; i<3; i++) cout << mod[i] << " ";
	cout << endl;
	cout << daynum%3 << endl;
	int mod1[3] = {};
	for(int i = 0; i<30; i++) for(int j = 0; j<30; j++) if(ans(i,j)) mod1[(i-j+3000)%3]++;
	for(int i = 0; i<3; i++) cout << mod1[i] << " ";
	cout << endl;
	cout << (daynum+1)%3 << endl;

}
