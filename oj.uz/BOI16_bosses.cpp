#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;
 
void solve() {
 
	int n;
	
	cin >> n;
	
	vector<vector<int>> g(n);
	vector<int> dist(n);
	i64 ans = LLONG_MAX;
	
	for(int i = 0; i < n; ++i) {
		int deg;
		cin >> deg;
		while(deg--) {
			int p;
			cin >> p;
			g[p - 1].push_back(i);
		}
	}
	
	for(int v = 0; v < n; ++v) {
		fill(dist.begin(), dist.end(), -1);
		
		queue<int> q;
		i64 sum_dist = 0;
		int vis = 0;
		
		q.push(v);
		dist[v] = 1;
		
		while(!q.empty()) {
			int v = q.front();
			q.pop();
			++vis;
			sum_dist += dist[v];
			for(int u : g[v]) {
				if(dist[u] != -1) continue;
				dist[u] = 1 + dist[v];
				q.push(u);
			}
		}
		
		if(vis == n) ans = min(ans, sum_dist);
	}
	
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
