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

const int N = 2e5 + 100;

int par[N], rk[N];

int findSet(int u) {
	return u == par[u] ? u : par[u] = findSet(par[u]);
}

bool join(int u, int v) {
	u = findSet(u);
	v = findSet(v);
	if(u == v) return false;
	if(rk[u] > rk[v]) swap(u, v);
	par[u] = v;
	rk[v] += rk[u] == rk[v];
	return true;
}

void solve() {

	int n, m;

	cin >> n >> m;

	vector<vector<int>> adj(n);
	vector<int> V;
	string s;

	iota(par, par + n, 0);

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		if(join(u, v)) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}		
	}	

	cin >> s;

	function<void(int, int)> dfs = [&](int u, int p) {
		V.push_back(u + 1);
		s[u] ^= 1;
		for(int v : adj[u]) {
			if(v == p) continue;
			dfs(v, u);
			V.push_back(u + 1);
			s[u] ^= 1;
			if(s[v] != '0') {
				V.push_back(v + 1);
				V.push_back(u + 1);
				s[v] ^= 1;
				s[u] ^= 1;
			}
		}
		if(u == p && s[u] != '0') {
			int v = adj[u][0];
			V.push_back(v + 1);
			V.push_back(u + 1);
			V.push_back(v + 1);
			s[u] ^= 1;
		}
	};

	dfs(0, 0);

	cout << V.size() << '\n';
	for(int i = 0; i < (int)V.size()- 1; ++i) cout << V[i] << ' ';
	cout << V.back() << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
