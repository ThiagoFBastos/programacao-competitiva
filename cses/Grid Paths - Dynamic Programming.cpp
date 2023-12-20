#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC target ("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const int mod = 1e9 + 7, maxn = 1001;
char grid[maxn][maxn];
int paths[maxn][maxn], n;
void dfs(int x, int y) {
	if(paths[x][y] != -1) return;
	int r = 0;
	paths[x][y] = 0;
	if(grid[x + 1][y] == '.') {
		dfs(x + 1, y); 
		r += paths[x + 1][y];
		if(r >= mod) r -= mod;
	}
	if(grid[x][y + 1] == '.') {
		dfs(x, y + 1); 
		r += paths[x][y + 1];
		if(r >= mod) r -= mod;
	}
	paths[x][y] = r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int k = 0; k < n; ++k) {
		cin >> grid[k];
		for(int j = 0; j < n; ++j)
			paths[k][j] = -1;
	}
	if(grid[0][0] == '.') {
		paths[n - 1][n - 1] = 1;
		dfs(0, 0);
	}
	cout << max(0, paths[0][0]) << '\n';
	return 0;
}
