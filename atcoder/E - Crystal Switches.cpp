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

const int N = 2e5 + 100;

vector<ii> adj[N];
int dist[2][N], n, m, k, inv[N];

void solve() {
	cin >> n >> m >> k;

	for(int i = 0; i < m; ++i) {
		int u, v, t;
		cin >> u >> v >> t;
		--u, --v;
		adj[u].pb({v, t});
		adj[v].pb({u, t});
	}

	while(k--) {
		int s;
		cin >> s;
		inv[s - 1] = 1;
	}

	queue<ii> q;

	for(int k = 0; k < 2; ++k)
	for(int i = 0; i < n; ++i)
		dist[k][i] = INF;

	for(int k : {0, 1}) {
		if(inv[0] >= k) {
			q.push({0, k});
			dist[k][0] = 0;
		}
	}

	while(!q.empty()) {
		auto [u, t] = q.front(); q.pop();
		for(auto [v, e] : adj[u]) {
			if(!(t ^ e)) continue;
			for(int k = 0; k <= inv[v]; ++k) {
				if(dist[k ^ t][v] != INF) continue;
				dist[k ^ t][v] = 1 + dist[t][u];
				q.push({v, k ^ t});
			}
		}
	}

	int d = min(dist[0][n - 1], dist[1][n - 1]);

	if(d == INF) {
		cout << "-1\n";
		return;
	}

	cout << d << '\n';
}	
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	//cin >> t;
    while(t--) solve();
    return 0;
}
