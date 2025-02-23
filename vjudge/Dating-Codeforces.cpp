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

const int N = 1e5 + 10, K = 17, B = 447;

int n, q, t[N], f[N], sp[K][N], frqf[2 * N], frqv[N], d[N], in[N], out[N], arr[2 * N], tms;
vector<int> adj[N];
i64 pairs, ans[N];

void dfs(int u, int p) {
	arr[tms] = u, in[u] = tms++;
	sp[0][u] = p;
	for(int i = 1; (1 << i) <= n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(int v : adj[u]) {
		if(v == p) continue;
		d[v] = 1 + d[u];
		dfs(v, u);
	}
	arr[tms] = u, out[u] = tms++;
}

int lca(int a, int b) {
	if(d[a] > d[b]) swap(a, b);
	int dist = d[b] - d[a];
	for(int i = 0; (1 << i) <= dist; ++i) if((dist >> i) & 1) b = sp[i][b];
	if(a == b) return a;
	for(int i = 31 - __builtin_clz(d[a]); i >= 0; --i) {
		if(sp[i][a] == sp[i][b]) continue;
		a = sp[i][a], b = sp[i][b];
	}
	return sp[0][a];
}

void add(int v) {
	++frqv[v];
	if(frqv[v] & 1) {
		pairs += frqf[f[v] ^ 1];
		++frqf[f[v]];	
	} else {
		pairs -= frqf[f[v] ^1];
		--frqf[f[v]];
	}
}

void rem(int v) {
	--frqv[v];
	if(frqv[v] & 1) {
		pairs += frqf[f[v] ^ 1];
		++frqf[f[v]];	
	} else {
		pairs -= frqf[f[v] ^1];
		--frqf[f[v]];
	}
}

struct query {
	int l, r, id, lca_v;
	i64 val;
};

inline i64 hilbertOrder(int x, int y, int pow, int rotate = 0) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	i64 subSquareSize = 1ll << (2*pow - 2);
	i64 ans = seg * subSquareSize;
	i64 add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

bool operator<(query q1, query q2) {
	return q1.val < q2.val;
}

void solve() {
	cin >> n;
	vector<ii> coords;
	for(int i = 0; i < n; ++i) cin >> t[i];
	for(int i = 0; i < n; ++i) {
		cin >> f[i];
		coords.pb({f[i], 0});
		coords.pb({f[i], 1});
	}
	sort(all(coords));
	coords.resize(unique(all(coords)) - coords.begin());
	for(int i = 0; i < n; ++i) f[i] = lower_bound(all(coords), ii(f[i], t[i])) - coords.begin();
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs(0, 0);
	cin >> q;
	vector<query> queries(q);
	for(int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		if(d[a] > d[b]) swap(a, b);
		int c = lca(a, b);
		if(c == a) queries[i] = {in[a], in[b], i, -1, hilbertOrder(in[a], in[b], 19)};
		else queries[i] = {out[a], in[b], i, c, hilbertOrder(out[a], in[b], 19)};
	}
	sort(all(queries));
	int lo = 0, hi = -1;
	for(auto [l, r, id, v, _] : queries) {
		while(hi < r) add(arr[++hi]);
		while(hi > r) rem(arr[hi--]);
		while(lo < l) rem(arr[lo++]);
		while(lo > l) add(arr[--lo]);
		ans[id] = pairs;
		if(v != -1) ans[id] += frqf[f[v] ^ 1];
	}	
	for(int i = 0; i < q; ++i) cout << ans[i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}