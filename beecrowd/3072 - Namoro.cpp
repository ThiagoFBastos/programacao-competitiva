#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

using TYPE = tuple<int, int, int, int>;

const int N = 1e5 + 100;
const int B = 318;
const int LG = 17;

vector<int> adj[N];
int n, q, F[N], gen[N], sp[LG][N], ind, flat[2 * N], in[N], out[N], depth[N];
TYPE query[N];
i64 resp[N];

int lca(int a, int b) {
	if(depth[a] > depth[b]) swap(a, b);
	for(int i = 0, d = depth[b] - depth[a]; (1 << i) <= d; ++i) {
		if(d & (1 << i))
			b = sp[i][b];
	}
	if(a == b) return a;
	for(int i = 31 - __builtin_clz(depth[a]); i >= 0; --i) {
		if(sp[i][a] == sp[i][b]) continue;
		a = sp[i][a], b = sp[i][b];
	}
	return sp[0][a];
}

void dfs(int u, int p) {
	flat[in[u] = ind++] = u;
	
	sp[0][u] = p;
	for(int i = 1; (1 << i) < n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];

	for(int v : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfs(v, u);
	}

	flat[out[u] = ind++] = u;
}

int frq[N], cnt[N][2];
i64 ans;

void upd(int u, int x) {
	frq[u] += x;	
	if(frq[u] & 1) {
		ans += cnt[F[u]][gen[u] ^ 1];
		++cnt[F[u]][gen[u]];
	} else {
		ans -= cnt[F[u]][gen[u] ^ 1];
		--cnt[F[u]][gen[u]];
	}
}

void solve() {
	map<int, int> hash;

	cin >> n;

	for(int i = 0; i < n; ++i) cin >> gen[i];

	for(int i = 0; i < n; ++i) {
		cin >> F[i];
		if(!hash.count(F[i])) hash[F[i]] = size(hash);
		F[i] = hash[F[i]];
	}

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;	
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(0, 0);

	cin >> q;

	for(int i = 0; i < q; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		if(in[u] > in[v]) swap(u, v);
		int x = lca(u, v);
		query[i] = x == u ? make_tuple(in[u], in[v], -1, i) : make_tuple(out[u], in[v], x, i);
	}

	sort(query, query + q, [](TYPE a, TYPE b) {
		get<0>(a) /= B;
		get<0>(b) /= B;
		return a < b;
	});

	int lo = 0, hi = -1;

	for(int i = 0; i < q; ++i) {
		auto [l, r, x, k] = query[i];

		while(hi < r) upd(flat[++hi], 1);
		while(hi > r) upd(flat[hi--], -1);
		while(lo < l) upd(flat[lo++], -1);
		while(lo > l) upd(flat[--lo], 1);

		if(x != -1) {
			upd(x, 1);
			resp[k] = ans;
			upd(x, -1);
		} else
			resp[k] = ans;
	}

	for(int i = 0; i < q; ++i) cout << resp[i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}