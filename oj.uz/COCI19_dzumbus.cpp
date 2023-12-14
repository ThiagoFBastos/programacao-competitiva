#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
const int N = 1e3 + 10;
const i64 INF = 1e16L;
 
i64 dp[N][2][N], C[2][N];
vector<int> adj[N];
int n, m, q, sz[N];
i64 D[N];
 
void dfs(int u, int p) {
	
	sz[u] = 1;
	dp[u][0][0] = 0;
 
	for(int v : adj[u]) {
		if(v == p) continue;
 
		dfs(v, u);
 
		for(int i = 0; i < 2; ++i) 
		for(int k = 0; k <= sz[u] + sz[v]; ++k) 
			C[i][k] = INF;
 
		for(int k = sz[u]; k >= 0; --k) {
			for(int i = sz[v]; i >= 0; --i) {
				C[0][k + i] = min(C[0][k + i], dp[u][0][k] + min(dp[v][0][i], dp[v][1][i]));
 
				C[1][k + i] = min(C[1][k + i], dp[u][1][k] + min(dp[v][0][i], dp[v][1][i]));
 
				C[1][k + i + 1] = min(C[1][k + i + 1], dp[u][1][k] + dp[v][0][i] + D[v]);
 
				C[1][k + i + 1] = min(C[1][k + i + 1], dp[u][0][k] + dp[v][1][i] + D[u]);
 
				C[1][k + i + 2] = min(C[1][k + i + 2], dp[u][0][k] + dp[v][0][i] + D[u] + D[v]);
			}
		}
 
		for(int i = 0; i < 2; ++i) 
		for(int k = 0; k <= sz[u] + sz[v]; ++k) 
			dp[u][i][k] = min(dp[u][i][k], C[i][k]);
		
		sz[u] += sz[v];
	}
}
 
struct uf {
	vector<int> par, rank, sz;
	
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
	cin >> n >> m;
 
	for(int i = 0; i < n; ++i) cin >> D[i];
 
	uf dsu(n + 1);
 
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		dsu.join(u, v);
	}
 
	for(int u = 0; u <= n; ++u)
	for(int k = 0; k < 2; ++k)
	for(int i = 0; i <= n; ++i)
		dp[u][k][i] = INF;
 
	D[n] = INF;
 
	for(int i = 0; i < n; ++i)
		if(dsu.join(n, i))
			adj[n].push_back(i);
 
	dfs(n, -1);
 
	vector<pair<i64, int>> A;
 
	for(int i = 0; i <= n; ++i) {
		if(dp[n][0][i] < INF)
			A.emplace_back(dp[n][0][i], i);
	}
 
	for(int i = (int)A.size() - 2; i >= 0; --i)
		A[i].first = min(A[i].first, A[i + 1].first);
 
	cin >> q;
 
	while(q--) {
		i64 x;
		cin >> x;
		auto it = prev(upper_bound(A.begin(), A.end(), make_pair(x, n + 1)));
		cout << it->second << '\n';	
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
 
