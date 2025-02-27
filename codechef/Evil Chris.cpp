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
using i128 = __int128;

const int N = 2e5 + 10;

int n, m, days, pairs;
int lo[N], hi[N], par[N], depth[N];
i64 st[N], sch[N];
map<ii, int> finish;
vector<tuple<int, int, int>> event[N];
vector<int> query[N];
tuple<int, int, int> couple[N];

int findSet(int u) {
	return u == par[u] ? u : par[u] = findSet(par[u]);
}

void join(int a, int b) {
	a = findSet(a); b = findSet(b);
	if(a == b) return;
	else if(depth[a] > depth[b]) swap(a, b);
	par[a] = b;
	depth[b] += depth[a] == depth[b];
	st[b] += st[a];
}

void solve() {
	cin >> n >> m >> days >> pairs;

	for(int i = 0; i < n; ++i) cin >> sch[i];

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		if(u > v) swap(u, v);
		--u, --v;
		finish[{u, v}] = 1;
	}

	for(int i = 0; i < days; ++i) {
		int t, a0, a1;
		cin >> t >> a0 >> a1;
		if(t == 1) {
			if(a0 > a1) swap(a0, a1);
			--a0, --a1;
			finish[{a0, a1}] = days - i + 1;
		} else {
			sch[--a0] -= a1;
			event[days - i + 1].pb({2, a0, a1});
		}
	}

	for(int i = 0; i < pairs; ++i) {
		int a, b, k;
		cin >> a >> b >> k;
		couple[i] = {a-1, b-1, k};
		lo[i] = 1, hi[i] = days + 2;
	}

	for(const auto& e : finish) event[e.sc].pb({1, e.fi.fi, e.fi.sc});

	for(int i = 1; (1 << i) <= 2 * days + 4; ++i) {
	
		for(int j = 1; j <= days + 1; ++j) query[j].clear();
		
		for(int u = 0; u < n; ++u) par[u] = u, depth[u] = 0, st[u] = sch[u];

		for(int j = 0; j < pairs; ++j) {
			if(lo[j] == hi[j]) continue;
			int mid = (lo[j] + hi[j]) / 2;
			query[mid].pb(j);
		}

		for(int d = 1; d <= days + 1; ++d) {
			for(const auto& e : event[d]) {
				int t, a0, a1;
				tie(t, a0, a1) = e;
				if(t == 1) join(a0, a1);
				else st[findSet(a0)] += a1;
			}

			for(int c : query[d]) {
				int u, v, k;
				tie(u, v, k) = couple[c];
				if(st[findSet(u)] + st[findSet(v)] >= k) hi[c] = d;
				else lo[c] = d + 1;
			}
		}
	}
	
	for(int i = 0; i < pairs; ++i)
		cout << days - hi[i] + 1 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}