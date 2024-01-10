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
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	DSU dsu(n);
	vector<int> cc(n);
	
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	for(auto& v : g) sort(v.rbegin(), v.rend());
	
	cc.back() = 0;
	
	for(int i = n - 1; i > 0; --i) {
		bool new_node = true;
		cc[i - 1] = cc[i];
		for(int v : g[i]) {
			if(v < i) break;
			if(dsu.join(v, i)) {
				if(new_node) new_node = false;
				else --cc[i - 1];
			}
		}
		if(new_node) ++cc[i - 1];
	}
	
	for(int x : cc) cout << x << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

