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

const int N = 1e5 + 10;

set<int> adj[N];
set<ii> G, compG;
int n, m, a, b, upd, degG[N], degCompG[N];

void solve() {
	cin >> n >> m >> a >> b;

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].insert(b);
		adj[b].insert(a);
	}

	for(int i = 0; i < n; ++i) {
		degG[i] = adj[i].size();		
		degCompG[i] = n - 1 - degG[i];
		G.emplace(degG[i], i);
		compG.emplace(degCompG[i], i);
	}

	G.emplace(INF, -1);
	compG.emplace(INF, -1);

	while(G.begin()->fi < a || compG.begin()->fi - upd < b) {
		
		int v = G.begin()->fi < compG.begin()->fi - upd ? G.begin()->sc : compG.begin()->sc;

		G.erase(ii(degG[v], v));
		compG.erase(ii(degCompG[v], v));
			
		for(int u : adj[v]) {
			adj[u].erase(v);
			G.erase(ii(degG[u]--, u));
			G.insert(ii(degG[u], u));
			compG.erase(ii(degCompG[u]++, u));
			compG.insert(ii(degCompG[u], u));
		}

		++upd, --n;
	}

	cout << n << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
