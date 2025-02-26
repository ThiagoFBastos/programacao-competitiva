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

const int N = 35000 + 10, K = 188, LOG = 16;

int n, q, a[N];
ii p[N];

set<int> sq[K];
set<ii> diffs[K];

void put(int x) {
	auto& A = sq[x / K];
	auto& B = diffs[x / K];
	auto it = A.lower_bound(x);
	if(it != A.end() && it != A.begin()) B.erase(ii(p[*it].fi - p[*prev(it)].fi, *prev(it)));
	if(it != A.end()) B.emplace(p[*it].fi - p[x].fi, x);
	if(it != A.begin()) --it, B.emplace(p[x].fi - p[*it].fi, *it);
	A.insert(x);
}

void del(int x) {
	auto& A = sq[x / K];
	auto& B = diffs[x / K];
	auto it = A.find(x);
	it = A.erase(it);
	if(it != A.end()) B.erase(ii(p[*it].fi - p[x].fi, x));
	if(it != A.begin()) --it, B.erase(ii(p[x].fi - p[*it].fi, *it)), ++it;
	if(it != A.end() && it != A.begin()) B.emplace(p[*it].fi - p[*prev(it)].fi, *prev(it));	
}

int parity[N];

void upd(int x) {
	parity[x] ^= 1;
	parity[x] ? put(a[x]) : del(a[x]);
}

vector<int> adj[N];
int in[N], out[N], paths[2 * N], t, d[N], sp[LOG][N];

void dfs(int u, int p) {
	paths[t] = u, in[u] = t++;
	sp[0][u] = p;
	for(int i = 1; i < LOG; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];
	for(int v : adj[u]) {
		if(v == p) continue;
		d[v] = 1 + d[u];
		dfs(v, u);
	}
	paths[t] = u, out[u] = t++;
}

int lca(int u, int v) {
	if(d[u] > d[v]) swap(u, v);
	int dist = d[v] - d[u];
	for(int i = 0; i < LOG; ++i) if((dist >> i) & 1) v = sp[i][v];
	if(u == v) return u;
	for(int i = LOG - 1; i >= 0; --i) {
		if(sp[i][u] == sp[i][v]) continue;
		u = sp[i][u], v = sp[i][v];
	}
	return sp[0][u];
}

struct query {
	int u, v, lca, id, type;
	i64 ord;
};

bool operator<(const query& q1, const query& q2) {
	return q1.ord < q2.ord;
}		

query reqs[N];
int ans[N];

void solve() {
	cin >> n;

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		p[i] = {a[i], i};
	}

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v); adj[v].pb(u);
	}

	sort(p, p + n);

	for(int i = 0; i < n; ++i) a[i] = lower_bound(p, p + n, ii(a[i], i)) - p;

	dfs(0, 0);

	cin >> q;

	for(int i = 0; i < q; ++i) {
		char type;
		int u, v;
		cin >> type >> u >> v;
		--u, --v;
		if(in[u] > in[v]) swap(u, v);
		int w = lca(u, v);
		if(w == u) reqs[i] = {in[u], in[v], -1, i, type == 'F', hilbertOrder(in[u], in[v], LOG)};
		else reqs[i] = {out[u], in[v], w, i, type == 'F', hilbertOrder(out[u], in[v], LOG)};
	}

	sort(reqs, reqs + q);

	int lo = 0, hi = -1;

	for(int i = 0; i < q; ++i) {
		auto [l, r, my_lca, id, type, _] = reqs[i];

		if(lo <= l) {
			while(hi < r) upd(paths[++hi]);
			while(hi > r) upd(paths[hi--]);
			while(lo < l) upd(paths[lo++]);
			while(lo > l) upd(paths[--lo]);
		} else {
			while(lo > l) upd(paths[--lo]);
			while(lo < l) upd(paths[lo++]);
			while(hi > r) upd(paths[hi--]);
			while(hi < r) upd(paths[++hi]);
		}

		if(type) {
			int min_v = INF, max_v = -INF;
			if(my_lca != -1) min_v = max_v = a[my_lca];
			for(int i = 0; i * K < n; ++i) {
				auto& A = sq[i];
				if(A.empty()) continue;
				min_v = min(min_v, *A.begin());
				max_v = max(max_v, *A.rbegin()); 
			}
			ans[id] = p[max_v].fi - p[min_v].fi;
		} else {
			int gap = INF, last = -INF;
			for(int i = 0; i * K < n; ++i) {
				auto& A = sq[i];
				auto& B = diffs[i];
				if(!B.empty()) gap = min(gap, B.begin()->fi);
				if(!A.empty()) {
					gap = min(gap, p[*A.begin()].fi - last);
					last = p[*A.rbegin()].fi;
					if(my_lca == -1) continue;
					int x = a[my_lca];
					auto it = A.lower_bound(x);
					if(it != A.end()) gap = min(gap, p[*it].fi - p[x].fi);
					if(it != A.begin()) --it, gap = min(gap, p[x].fi - p[*it].fi);
				}
			}
			ans[id] = gap;
		}
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