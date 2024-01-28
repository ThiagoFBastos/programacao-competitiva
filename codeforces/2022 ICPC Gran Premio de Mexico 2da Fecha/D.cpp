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
	int n, m;
	cin >> n >> m;
	vector<vector<ii>> adj(n);
	vector<int> d(n, -1);
	queue<int> q;
	for(int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		adj[a].pb({b, c});	
		adj[b].pb({a, c});
	}	
	d[0] = 0;
	q.push(0);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(auto [v, w] : adj[u]) {
			if(d[v] != -1) continue;
			d[v] = d[u] + 1;
			q.push(v);		
		}
	}
	i64 ans = 0;
	for(int i = 0; i < n; ++i) {
		int e = INF;
		for(auto [j, w] : adj[i]) {
			if(d[j] + 1 != d[i]) continue;
			e = min(e, w);
		}
		ans += (i64)e * d[i];
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

