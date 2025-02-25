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

const int N = 4e4 + 10;

int n, q, cnt[N], sum[N];
vector<int> G1[N], G2[N];

vector<int> findfarthest(vector<int> G[], int n) {
	vector<int> e(n), maxdown(n), maxup(n), depth(n);
	
	auto dfsdown = [&](auto&& dfsdown, int u, int p) {
		if(p < 0) return;
		maxdown[u] = depth[u];
		for(int v : G[u]) {
			if(v == p) continue;
			depth[v] = 1 + depth[u];
			dfsdown(dfsdown, v, u);
			maxdown[u] = max(maxdown[u], maxdown[v]);
		}
	};

	depth[0] = 0;
	dfsdown(dfsdown, 0, 0);

	auto dfsfarthest = [&](auto&& dfsfarthest, int u, int p) {
		if(p < 0) return;
		int best[2] = {-INF, -INF};
		for(int v : G[u]) {
			if(v == p) continue;
			else if(best[0] < maxdown[v]) best[1] = best[0], best[0] = maxdown[v];
			else best[1] = max(best[1], maxdown[v]);
		}	
		e[u] = max(maxdown[u] - depth[u], maxup[u] + depth[u]);
		for(int v : G[u]) {
			if(v == p) continue;	
			maxup[v] = max(maxup[u], best[maxdown[v] == best[0]] - 2 * depth[u]);
			dfsfarthest(dfsfarthest, v, u);
		}
	};

	maxup[0] = 0;
	dfsfarthest(dfsfarthest, 0, 0);

	return e;
}

void solve() {
	cin >> n >> q;

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G1[u].pb(v); G1[v].pb(u);
	}

	for(int i = 1; i < q; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G2[u].pb(v); G2[v].pb(u);
	}

	auto e1 = findfarthest(G1, n);
	auto e2 = findfarthest(G2, q);
	int d1 = *min_element(all(e1)), d2 = *min_element(all(e2));
	double ans = 0;

	d1 = 2 * d1 - count(all(e1), d1) + 1;
	d2 = 2 * d2 - count(all(e2), d2) + 1;
	
	if(d1 > d2) {
		swap(n, q);
		swap(d1, d2);
		swap(e1, e2);
	}

	for(int v = 0; v < n; ++v) {
		++cnt[e1[v]];
		sum[e1[v]] += e1[v] + 1;
	}

	for(int i = 1; i <= max(n, q); ++i) {
		cnt[i] += cnt[i - 1];
		sum[i] += sum[i - 1];
	}

	for(int v = 0; v < q; ++v) {
		int t = cnt[max(n, q)] - cnt[d2 - e2[v] - 1]; 	
		ans += t * e2[v];
 		ans += sum[max(n, q)] - sum[d2 - e2[v] - 1];
		ans += (n - t) * d2;
	}

	cout << fixed << setprecision(3) << ans / double(n * q) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}