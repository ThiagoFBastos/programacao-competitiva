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

const int N = 2e5 + 100, MOD = 998244353;

struct FN {
	int c, d;
	FN operator^(FN other) {
		int D = (d + (i64)c * other.d) % MOD;
		int C = (i64)c * other.c % MOD;
		return {C, D};
	}
	int evaluate(int x) {
		return ((i64)c * x + d) % MOD;
	}
};

vector<int> adj[N];
int head[N];
int in[N], out[N], sz[N], depth[N], par[N];
FN st[2 * N][2], f[2][N];
int n, q;

struct hld {
	int tms;

	void build(FN f[]) {
		for(int i = 0; i < n; ++i) {
			st[i + n][0] = f[i];
			st[i + n][1] = f[n - i - 1];
		}
		for(int i = n - 1; i; --i)
			for(int j = 0; j < 2; ++j)
				st[i][j] = st[2 * i][j] ^ st[2 * i + 1][j];
	}

	FN query(int k, int l, int r) {
		FN f = {1, 0}, g = {1, 0};
		for(l += n, r += n; l <= r; l /= 2, r /= 2) {
			if(l & 1) f = f ^ st[l++][k];
			if(~r & 1) g = st[r--][k] ^ g;
		}
		return f ^ g;
	}

	void upd(int i, int k, FN f) {
		st[k += n][i] = f;
		for(k /= 2; k; k /= 2) st[k][i] = st[2 * k][i] ^ st[2 * k + 1][i];
	}

	FN queryPath(int a, int b) {
		FN f = {1, 0}, g = {1, 0};
		
		while(head[a] != head[b]) {
			if(depth[head[a]] > depth[head[b]]) {
				f = f ^ query(1, n - in[a] - 1, n - in[head[a]] - 1);
				a = par[head[a]];
			} else {
				g = query(0, in[head[b]], in[b]) ^ g;
				b = par[head[b]];
			}
		}
		
		if(depth[a] > depth[b]) f = f ^ query(1, n - in[a] - 1, n - in[b] - 1);
		else g = query(0, in[a], in[b]) ^ g;

		return f ^ g;
	}

	void updNode(int a, FN f) {
		upd(0, in[a], f);
		upd(1, n - in[a] - 1, f);
	}

	void dfssize(int u, int p) {
		int t = 1;
		par[u] = p;
		for(int& v : adj[u]) {
			if(v == p) continue;
			depth[v] = 1 + depth[u];
			dfssize(v, u);
			t += sz[v];
			if(sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
		}
		sz[u] = t;
	}

	void dfshld(int u, int p) {
		in[u] = tms++;
		for(int v : adj[u]) {
			if(v == p) continue;	
			else if(2 * sz[v] >= sz[u]) head[v] = head[u];
			dfshld(v, u);
		}
		out[u] = tms - 1;
	}
		
	hld() {
		for(int i = 0; i < n; ++i) head[i] = i;
		dfssize(0, 0);
		tms = 0;
		dfshld(0, 0);
		for(int i = 0; i < n; ++i) f[1][in[i]] = f[0][i];
		build(f[1]);
	}
};

void solve() {
	cin >> n >> q;

	for(int i = 0; i < n; ++i) {
		int c, d;
		cin >> c >> d;
		f[0][i] = {c, d};
	}

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v); adj[v].pb(u);
	}
	
	hld S;

	while(q--) {
		int type, a0, a1, a2;
		cin >> type >> a0 >> a1 >> a2;
		if(type == 0) S.updNode(a0, {a1, a2});
		else cout << S.queryPath(a1, a0).evaluate(a2) << '\n';
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