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

	int n, k;

	cin >> n >> k;

	vector<bool> root(n, true);
	vector<int> x(n), cycle(n, -1), cycle_sz(n, 0), deg(n, 0);
	int id = 0;
	queue<int> q;
	bitset<1001> dp;
	DSU dsu(n);

	for(int i = 0; i < n; ++i) {
		cin >> x[i];
		if(--x[i] != i) ++deg[x[i]];
	}

	for(int v = 0; v < n; ++v) {
		if(deg[v]) continue;
		cycle[v] = id;
		cycle_sz[id++] = 1;
		q.push(v);
	}

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		if(x[u] == u) continue;
		if(--deg[x[u]] == 0) {
			cycle[x[u]] = id;
			cycle_sz[id++] = 1;
			q.push(x[u]);
		}
	}

	for(int v = 0; v < n; ++v) {
		if(cycle[v] != -1) continue;
		for(int u = v; cycle[u] == -1; u = x[u]) {
			cycle[u] = id;
			cycle_sz[id]++;
		}
		++id;
	}

	for(int w = 0; w < n; ++w) {
		int u = cycle[x[w]];
		int v = cycle[w];
		if(u == v) continue;
		dsu.join(u, v);
		root[v] = false;
	}

	dp[0] = 1;

	for(int v = 0; v < id; ++v) {
		if(!root[v]) continue;

		int u = dsu.findSet(v);
		int L = cycle_sz[v], R = dsu.sz[u] + cycle_sz[v] - 1;
		
		bitset<1001> S;

		for(int i = L; i <= R; ++i) S[i] = 1;
		
		for(int i = k; i >= 0; --i) {
			if(!dp[i]) continue;
			dp |= S << i;
		}
	}

	for(int i = k; i >= 0; --i) {
		if(!dp[i]) continue;
		cout << i << '\n';
		break;
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}