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

void solve() {
	int n, m, l, u;

	cin >> n >> m >> l >> u;

	vector<vector<ii>> adj(n);
	vector<i64> cost(n, INFLL);
	set<tuple<i64, int>> pq;

	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}	

	pq.emplace(0ll, 0);

	while(!pq.empty()) {
		auto [c, u] = *pq.begin();
		pq.erase(pq.begin());
		if(cost[u] != INFLL) continue;
		cost[u] = c;
		for(auto [v, w] : adj[u]) {
			if(cost[v] != INFLL) continue;
			pq.emplace(w + c, v);
		}
	}

	set<ii> ed;

	for(int a = 0; a < n; ++a) {
		for(auto [b, w] : adj[a]) {
			i64 c = cost[a];
			if(2 * c < u) ed.emplace(min(a, b), max(a, b));
		}
	}

	cout << ed.size() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
