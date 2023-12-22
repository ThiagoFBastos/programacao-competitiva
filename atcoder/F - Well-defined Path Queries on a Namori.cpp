#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e5 + 100;

vector<int> adj[N];
int deg[N], sub[N];

void solve() {
	int n;
	queue<int> q;

	cin >> n;

	for(int i = 0; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		++deg[u], ++deg[v];
	}

	for(int i = 0; i < n; ++i) if(deg[i] == 1) q.push(i);
	
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : adj[u]) if(--deg[v] == 1) q.push(v);
	}

	for(int i = 0; i < n; ++i) if(deg[i] > 1) sub[i] = -1;

	function<void(int, int)> dfs = [&](int u, int x) {
		for(int v : adj[u]) {
			if(sub[v]) continue;
			sub[v] = x;
			dfs(v, x);
		}
	};

	for(int i = 0; i < n; ++i) {
		if(sub[i] != -1) continue;
		dfs(i, i + 1);
	}

	int m;

	cin >> m;

	while(m--) {
		int u, v;
		cin >> u >> v;
		--u, --v;

		if(sub[u] > 0) swap(u, v);

		if(sub[u] < 0 && sub[v] < 0) cout << "No\n";
		else if(sub[u] < 0) {
			if(u + 1 == sub[v]) cout << "Yes\n";
			else cout << "No\n";
		} else if(sub[u] == sub[v]) cout << "Yes\n";
		else cout << "No\n";
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
