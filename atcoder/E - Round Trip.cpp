#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	
	int h, w;

	cin >> h >> w;

	vector<string> g(h);
	vector<vector<int>> low(h), t(h);
	int x0 = -1, y0 = -1;

	for(int i = 0; i < h; ++i) {
		cin >> g[i];
		low[i].assign(w, -1);
		t[i].assign(w, -1);
	}

	ii delta[] = {
		{0, 1},
		{0, -1},
		{1, 0},
		{-1,0}
	};	

	for(int i = 0; i < h; ++i)
		for(int j = 0; j < w; ++j)
			if(g[i][j] == 'S') x0 = i, y0 = j;

	int tms = 0;

	function<void(int,int,int,int)> dfs = [&](int i, int j, int pi, int pj) {
		low[i][j] = ii(x0, y0) == ii(i, j) ? INF : tms;
		t[i][j] = tms++;	
		for(auto [dx, dy] : delta) {
			int x = i + dx, y = j + dy;
			if(x < 0 || y < 0 || x >= h || y >= w || g[x][y] == '#') continue;
			if(t[x][y] < 0) {
				dfs(x, y, i, j);
				low[i][j] = min(low[i][j], low[x][y]);
			} else if(ii(x, y) != ii(pi, pj))
				low[i][j] = min(low[i][j], t[x][y]);
		}
	};

	dfs(x0, y0, -1, -1);

	cout << (low[x0][y0] == 0 ? "Yes\n" : "No\n");
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
