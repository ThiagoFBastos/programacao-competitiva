#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
#define f first
#define s second
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100000
#define MOD 1000000007
vii dag[MAXN];
ll cost[MAXN];
int paths[MAXN], minpath[MAXN], maxpath[MAXN];
void dfs(int v) {
	ll p = 0;
	int maxp = -1e9, minp = 1e6;
	paths[v] = 0;
	for(auto [u, du] : dag[v]) {
		if(paths[u] == -1)
			dfs(u);
		maxp = max(maxp, maxpath[u]);
		minp = min(minp, minpath[u]);
		p += paths[u];
	}
	paths[v] = p % MOD;
	maxpath[v] = 1 + maxp;
	minpath[v] = 1 + minp;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	vii G[MAXN];
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	int n, m;
	cin >> n >> m;
	for(int k = 0; k < m; ++k) {
		int u, v, c;
		cin >> u >> v >> c;
		G[u - 1].push_back({v - 1, c});
	}
	for(int v = 0; v < n; ++v) {
		cost[v] = -1;
		paths[v] = -1;
	}
	pq.push({0, 0});
	while(!pq.empty()) {
		auto [dv, v] = pq.top();
		pq.pop();
		if(cost[v] == -1) {
			cost[v] = dv;
			if(v == n - 1) break;
			for(auto [u, du] : G[v]) {
				if(cost[u] == -1)
					pq.push({du + dv, u});
			}
		}
	}
	for(int v = 0; v < n; ++v) {
		for(auto [u, du] : G[v]) {
			if(cost[v] + du == cost[u])
				dag[v].push_back({u, du});
		}
	}
	maxpath[n - 1] = minpath[n - 1] = 0;
	paths[n - 1] = 1;
	dfs(0);
	cout << cost[n - 1] << ' ' << paths[0] << ' ' << minpath[0] << ' ' << maxpath[0] << '\n';
	return 0;
} 
