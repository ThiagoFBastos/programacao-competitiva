#pragma GCC optimize("O3,unroll-loops")
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

const int N = 1e5 + 100, B = 500, K = 17;

vector<int> adj[N];
int presnt[N], frqV[N], frqP[N];
int in[N], out[N];
int sp[K][N], depth[N];
int n, m, t, cntPresnts;
ii tour[2 * N];

void upd(ii x) {
	auto [v, p] = x;
	frqV[v] *= -1;
	cntPresnts -= !!frqP[p];
	frqP[p] += frqV[v];
	cntPresnts += !!frqP[p];
}

void dfs(int u, int p) {
	tour[t] = {u, presnt[u]}, in[u] = t++;
	sp[0][u] = p;
	for(int i = 1; (1 << i) <= n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(int v : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfs(v, u);
	}
	tour[t] = {u, presnt[u]}, out[u] = t++;
}

int lca(int a, int b) {
	if(depth[a] > depth[b]) swap(a, b);
	int d = depth[b] - depth[a];
	for(int i = 0; (1 << i) <= d; ++i) if((d >> i) & 1) b = sp[i][b];
	if(a == b) return a;
	for(int i = 31 - __builtin_clz(n); i >= 0; --i) {
		if(sp[i][a] == sp[i][b]) continue;
		a = sp[i][a], b = sp[i][b];
	}
	return sp[0][a];
}

using QUERY = tuple<int, int, int, int>;

QUERY query[N];
int ans[N];

void solve() {
	map<string, int> id;

	cin >> n >> m;

	memset(frqV, -1, sizeof(int) * n);

	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		if(!id.count(s)) id[s] = id.size();
		presnt[i] = id[s];
	}

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	dfs(0, 0);

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		if(in[a] > in[b]) swap(a, b);
		int c = lca(a, b);
		if(c == a) query[i] = {in[a], in[b], -1, i};
		else query[i] = {out[a], in[b], c, i};
	}

	sort(query, query + m, [](QUERY a, QUERY b) {
		get<0>(a) /= B;
		get<0>(b) /= B;
		return a < b;
	});

	int lo = 0, hi = -1;

	for(int i = 0; i < m; ++i) {
		auto [l, r, c, pos] = query[i];

		while(hi < r) upd(tour[++hi]);
		while(hi > r) upd(tour[hi--]);		
		while(lo < l) upd(tour[lo++]);
		while(lo > l) upd(tour[--lo]);

		ans[pos] = cntPresnts + (c != -1 && (!frqP[presnt[c]]));
	}

	for(int i = 0; i < m; ++i) cout << ans[i] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}