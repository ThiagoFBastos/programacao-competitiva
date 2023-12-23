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

using C = tuple<int, int, int>;

const int N = 5e5 + 100;

vector<ii> adj[N], A[N];

void add(int x, int y, int z) {
	A[x].pb({y, z});
}

void solve() {
	int n, m;
	map<ii, int> ID;

	cin >> n >> m;

	for(int i = 0; i < m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		--u, --v;
		if(!ID.count(ii(c, v))) ID[{c, v}] = ID.size();
		if(!ID.count(ii(c, u))) ID[{c, u}] = ID.size();
		adj[u].pb({c, v});
		adj[v].pb({c, u});
	}

	for(int u = 0; u < n; ++u) {
		ID[{-1, u}] = ID.size();
		for(auto [x, v] : adj[u]) {
			add(ID[{x, u}], ID[{-1, u}], 0);
			add(ID[{-1, u}], ID[{x, u}], 1);
			add(ID[{x, u}], ID[{x, v}], 0);
		}
	}

	set<ii> pq;
	vector<bool> vis(ID.size(), false);

	pq.emplace(0, ID[{-1, 0}]);

	while(!pq.empty()) {
		auto [x, v] = *pq.begin(); pq.erase(pq.begin());
		if(vis[v]) continue;
		if(v == ID[{-1, n - 1}]) {
			cout << x << '\n';
			return;
		}
		vis[v] = true;
		for(auto [u, w] : A[v]) {
			if(vis[u]) continue;
			pq.emplace(w + x, u);
		}
	}

	cout << "-1\n";
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
