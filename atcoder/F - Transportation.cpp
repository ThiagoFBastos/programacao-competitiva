#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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
using i128 = __int128;

struct uf {
	vector<int> par, rank, sz;

	uf() {}

	uf(int n) {
		par.resize(n);
		rank.assign(n, 0);
		sz.assign(n, 1);
		iota(par.begin(), par.end(), 0);
	}
	
	int findSet(int v) {
		return v == par[v] ? v : par[v] = findSet(par[v]);
	}

	bool same(int a, int b) {
		return findSet(a) == findSet(b);
	}
	
	bool join(int a, int b) {
		a = findSet(a);
		b = findSet(b);

		if(a == b) return false;
		else if(rank[a] > rank[b]) swap(a, b);
		
		par[a] = b;
		rank[b] += rank[a] == rank[b];
		sz[b] += sz[a];

		return true;
	}
};

void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> x(n), y(n);
	vector<tuple<int, int, int>> z(m);
	for(int& v : x) cin >> v;
	for(int& v : y) cin >> v;
	for(auto& [w, u, v] : z) {
		cin >> u >> v >> w;
		--u, --v;
	}
	i64 ans = INFLL;
	for(int i = 0; i < 4; ++i) {
		uf dsu(n + 2);
		i64 weight = 0;
		bool ok = true;
		auto e = z;
		if(i & 1) for(int j = 0; j < n; ++j) e.pb({x[j], n, j});
		if(i & 2) for(int j = 0; j < n; ++j) e.pb({y[j], n + 1, j});
		sort(all(e));
		for(auto [w, u, v] : e) if(dsu.join(u, v)) weight += w;
		for(int i = 0; i < n; ++i) ok = ok && dsu.same(i, 0);
		if(ok) ans = min(ans, weight);
	}
	cout << ans << '\n';
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
