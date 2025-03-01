#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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
	int n, q;
	
	cin >> n >> q;
	
	vector<tuple<int, int, int>> edge(n - 1);
	vector<unordered_map<int, int>> queries(n);
	vector<i64> ans(q, 0);
	DSU dsu(n);
	
	for(int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		edge[i - 1] = {0, p - 1, i};
	}
	
	for(int i = 0; i < n - 1; ++i) cin >> get<0>(edge[i]);
	
	sort(edge.begin(), edge.end());
	
	for(int i = 0; i < q; ++i) {
		int m;
		cin >> m;
		while(m--) {
			int v;
			cin >> v;
			++queries[--v][i];
		}
	}
	
	for(auto [w, u, v] : edge) {
		int x = dsu.findSet(u), y = dsu.findSet(v);
		
		if(queries[x].size() > queries[y].size()) swap(queries[x], queries[y]);
		
		for(auto [a, b] : queries[x]) {
			auto it = queries[y].find(a);
			if(it == queries[y].end()) continue;
			ans[a] += (i64)b * it->second * w;
		}
		
		for(auto [a, b] : queries[x]) queries[y][a] += b;
		
		dsu.join(x, y);
		
		if(dsu.findSet(x) != y) swap(queries[x], queries[y]);
	}
	
	for(i64 v : ans) cout << v << ' ';
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}
