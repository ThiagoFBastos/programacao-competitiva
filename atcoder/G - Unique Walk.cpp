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
	int n, m, e;

	cin >> n >> m;

	vector<vector<ii>> adj(n), adjCC(n);
	vector<bool> special(m, false), good(n, false);
	vector<int> cc(n, -1);

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb({v, i});
		adj[v].pb({u, i});
	}

	cin >> e;	

	for(int i = 0; i < e; ++i) {
		int id;
		cin >> id;
		special[id - 1] = true;
	}

	int t = 0, T = 0;

	auto dfs = [&](auto& dfs, auto& adj, int u, int t)->void {
		cc[u] = t;
		for(auto [v, k] : adj[u]) {
			good[t] = good[t] || special[k];
			if(cc[v] != -1 || special[k]) continue;
			dfs(dfs, adj, v, t);
		}
	};

	for(int i = 0; i < n; ++i) {
		if(cc[i] == -1) {
			dfs(dfs, adj, i, t);
			++t;
		}
	}

	for(int i = 0; i < n; ++i) {
		for(auto [j, k] : adj[i]) {
			if(!special[k] || cc[i] >= cc[j]) continue;
			adjCC[cc[i]].pb({cc[j], 0});
			adjCC[cc[j]].pb({cc[i], 0});
		}
	}

	fill(all(cc), -1);
	fill(all(special), false);

	int cnt[2] = {0};

	for(int i = 0; i < t; ++i) {
		if(good[i]) {
			if(cc[i] == -1) {
				dfs(dfs, adjCC, i, T);
				++T;
			}
			++cnt[adjCC[i].size() % 2];
		}
	}

	if(T == 1 && (!cnt[1] || cnt[1] == 2)) cout << "Yes\n";
	else cout << "No\n";
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
