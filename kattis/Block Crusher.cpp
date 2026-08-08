#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

string g[20];
bitset<181> memo[20][60];
int a, b, c;

bool backtrack(int x, int y, int z) {
	if(x < 0 || y < 0 || x == a || y == b || memo[x][y][z] || (z -= g[x][y] - '0') < 0) return false;
	char ch = g[x][y];
	g[x][y] = ' ';
	memo[x][y][z] = 1;
	if(x == a - 1) {
		for(int k = 0; k < a; ++k) cout << g[k] << '\n';
		cout << '\n';
		return true;
	}
	for(int dx = -1; dx <= 1; ++dx) {
		for(int dy = -1; dy <= 1; ++dy) {
			if(backtrack(x + dx, y + dy, z)) return true;
		}
	}
	g[x][y] = ch;
	return false;
}

void solve() {
	cin >> a >> b;
	if(!a) exit(0);
	c = 9 * a;
	for(int k = 0; k < a; ++k) {
		cin >> g[k];	
		for(int j = 0; j < b; ++j) memo[k][j].reset();
	}
	for(int k = 1; k <= c; ++k) {
		for(int j = 0; j < b; ++j)
			if(backtrack(0, j, k)) return;
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
	return 0;
}