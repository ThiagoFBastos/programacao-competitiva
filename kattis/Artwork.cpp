#include "bits/stdc++.h"

using namespace std;

using T = tuple<int, int, int, int>;
using ii = pair<int, int>;

const int N = 1e3 + 10;

int g[N][N];
bool visto[N][N];

int dx[][2] = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};

struct DSU {
	vector<int> pai, rank, sz;
	
	DSU(int n) {
		pai.resize(n);
		rank.assign(n, 0);
		sz.assign(n, 1);
		iota(pai.begin(), pai.end(), 0);
	}
	
	int findSet(int v) {
		return v == pai[v] ? v : pai[v] = findSet(pai[v]);
	}
	
	bool join(int a, int b) {
		a = findSet(a);
		b = findSet(b);
		if(a == b) return false;
		else if(rank[a] > rank[b]) swap(a, b);
		pai[a] = b;
		rank[b] += rank[a] == rank[b];
		sz[b] += sz[a];
		return true;
	}
};

void solve() {
	int n, m, q;
	cin >> n >> m >> q;
	
	vector<T> queries(q);
	vector<int> ans(q);
	DSU dsu((n + 1) * (m + 1));
	
	for(int i = 0; i < q; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		queries[i] = {x1, y1, x2, y2};
		++g[x1][y1];
		--g[x1][y2 + 1];
		--g[x2 + 1][y1];
		++g[x2 + 1][y2 + 1];
	}
	
	int cc = n * m;
	
	for(int x = 1; x <= n; ++x)
		for(int y = 1; y <= m; ++y)
			g[x][y] += g[x - 1][y] + g[x][y - 1] - g[x - 1][y - 1];
		
	for(int x = 1; x <= n; ++x) {
		for(int y = 1; y <= m; ++y) {
			if(g[x][y]) {
				--cc;
				continue;
			}
			for(int k = 0; k < 4; ++k) {
				int X = dx[k][0] + x, Y = dx[k][1] + y;
				if(X <= 0 || Y <= 0 || X > n || Y > m || g[X][Y]) continue;
				if(dsu.join(X * m + Y, x * m + y)) --cc;	
			}
		}
	}
	
	ans.back() = cc;
	
	for(int i = q - 1; i > 0; --i) {
		auto [x1, y1, x2, y2] = queries[i];
		
		for(int x = x1; x <= x2; ++x)
		for(int y = y1; y <= y2; ++y) if(--g[x][y] == 0) ++cc;
		
		for(int x = x1; x <= x2; ++x)
		for(int y = y1; y <= y2; ++y) {
			if(g[x][y]) continue;
			for(int k = 0; k < 4; ++k) {
				int X = dx[k][0] + x, Y = dx[k][1] + y;
				if(X <= 0 || Y <= 0 || X > n || Y > m || g[X][Y]) continue;
				if(dsu.join(X * m + Y, x * m + y)) --cc;	
			}
		}
		
		ans[i - 1] = cc;
	}
	
	for(int x : ans) cout << x << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}