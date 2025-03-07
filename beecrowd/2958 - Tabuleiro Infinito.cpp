#include <iostream>
#include <cmath>

using namespace std;

int min(int, int);

int main(){

	int e, d;

	cin >> e >> d;

	if((e = min(e, d)))
		cout << e << endl;
	else
		cout << "IMPOSSIVEL" << endl;
}

int min(int a, int b){

	int g[100], j = 0, r;
	int x, y;
	
	g[1] = 0;

	if(a < b){
		
		x = a;
		a = b;
		b = x;
	}

	x = a;
	y = b;

	while((r = a % b)){

		g[j++] = -a / b;
		a = b;
		b = r;
	}

	if(b > 1) 
		return 0;

	g[j] = 1;

	for(j = j - 2; j >= 0; --j)
		g[j] = g[j + 2] + g[j + 1] * g[j];
	
	return abs(g[0]) + abs(g[1]);
}