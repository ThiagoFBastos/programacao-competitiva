#pragma GCC optimize("O3")
#pragma GCC target("popcnt")

#include "bits/stdc++.h"

using namespace std;

const int N = 1e2;
int g[N][N], t;

string str = "ATGC";

struct DSU {
	vector<int> pai, rank;
	
	DSU(int n) {
		pai.resize(n);
		rank.assign(n, 0);
		iota(pai.begin(), pai.end(), 0);
	}
	
	int findSet(int v) {
		return v == pai[v] ? v : findSet(pai[v]);
	}
	
	void join(int a, int b) {
		if(rank[a] > rank[b]) swap(a, b);
		pai[a] = b;
		rank[b] += rank[a] == rank[b];
	}
};

void solve() {
	int n, m;
	
	cin >> n >> m;
	
	if(!n) exit(0);
	
	vector<string> w(n);
	vector<bitset<1000>> a(n);
	
	for(int i = 0; i < n; ++i) {
		cin >> w[i];
		for(int j = 0; j < n; ++j) g[i][j] = 0;
	}
	
	for(int i = 0; i < 4; ++i) {
		for(int k = 0; k < n; ++k) {
			a[k].reset();
			for(int j = 0; j < m; ++j) a[k][j] = int(w[k][j] == str[i]);
		}
		
		for(int k = 0; k < n; ++k) {
			for(int j = k + 1; j < n; ++j) {
				int cnt = (a[k] ^ a[j]).count();
				g[k][j] += cnt;
				g[j][k] += cnt;
			}
		}
	}
	
	vector<tuple<int, int, int>> edge;

	for(int u = 0; u < n; ++u)
	for(int v = u + 1; v < n; ++v)
		edge.emplace_back(make_tuple(g[u][v] / 2, u, v));
			
	sort(edge.begin(), edge.end());
	
	DSU dsu(n);
	int ans = 0;
	
	for(auto [cst, u, v] : edge) {
		u = dsu.findSet(u);
		v = dsu.findSet(v);
		if(u == v) continue;
		ans += cst;
		dsu.join(u, v);
	}
	
	cout << "Instancia " << ++t << '\n' << ans << "\n\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	for(;;) solve();
	return 0;
}