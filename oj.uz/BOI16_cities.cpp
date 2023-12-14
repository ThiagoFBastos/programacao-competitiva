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
 
const int N = 2e5 + 10, K = 5;
int n, m, k, city[K];
vector<ii> adj[N];
i64 cost[N][1 << K];
bool vis[N][1 << K];
 
void solve() {
 
	cin >> n >> k >> m;
 
	for(int i = 0; i < k; ++i) {
		cin >> city[i];
		--city[i];
	}
 
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < (1 << k); ++j)
			cost[i][j] = INFLL;	
 
	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}
 
	for(int i = 0; i < k; ++i) cost[city[i]][1<<i] = 0;
 
	for(int i = 1; i < k; ++i) {
		priority_queue<tuple<i64, int, int>> pq;
 
		for(int v = 0; v < n; ++v) {
			for(int j = 0; j < (1 << k); ++j) {
				if(__builtin_popcount(j) != i) continue;
				pq.emplace(-cost[v][j], v, j);		
			}
		}
 
		while(!pq.empty()) {
			auto [c, v, mask] = pq.top(); pq.pop();
			if(vis[v][mask]) continue;
			vis[v][mask] = true;		
			for(auto [u, w] : adj[v]) {
				i64 C = -c + w;
				if(C >= cost[u][mask]) continue;
				cost[u][mask] = C;
				pq.emplace(-C, u, mask);
			}
		}
 
		for(int v = 0; v < n; ++v) {
			for(int j = 0; j < (1 << k); ++j) {
				if(__builtin_popcount(j) != i + 1) continue;
				for(int S = j; S; S = (S - 1) & j)
					cost[v][j] = min(cost[v][j], cost[v][S] + cost[v][S ^ j]);
			}
		}
	}
 
	i64 best = INFLL;
	for(int v = 0; v < n; ++v) best = min(best, cost[v][(1<<k)-1]);
	cout << best << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
