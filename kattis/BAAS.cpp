#include "bits/stdc++.h"

using namespace std;

void solve() {
	int n;
	cin >> n;
	
	vector<int> t(n), deg(n), d(n), dp(n);
	vector<vector<int>> g(n);
	
	for(int& v : t) cin >> v;
	
	for(int i = 0; i < n; ++i) {
		cin >> deg[i];
		for(int j = 0; j < deg[i]; ++j) {
			int k;
			cin >> k;
			g[k - 1].push_back(i);
		}
	}
	
	int sc = INT_MAX;
	
	for(int v = 0; v < n; ++v) {
		int tv = t[v], tmax = 0;
		queue<int> q;
		t[v] = 0;
		for(int u = 0; u < n; ++u) {
			d[u] = deg[u];
			dp[u] = 0;
			if(!d[u]) q.push(u);
		}
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int v : g[u]) {
				dp[v] = max(dp[v], dp[u] + t[u]);
				if(--d[v] == 0) q.push(v);
			}
		}
		for(int v = 0; v < n; ++v) tmax = max(tmax, t[v] + dp[v]);
		sc = min(sc, tmax);
		t[v] = tv;
	}
	
	cout << sc << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}