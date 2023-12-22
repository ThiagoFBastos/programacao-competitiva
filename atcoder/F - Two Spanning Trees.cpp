#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 2e5 + 100;

vector<int> g[N];
bool vis[N];
int n, m;
vector<ii> T1, T2;

void dfs(int u) {
	vis[u] = true;
	for(int v : g[u]) {
		if(vis[v]) continue;
		T1.emplace_back(u + 1, v + 1);
		dfs(v);
	}
}

void bfs(int u) {
	queue<int> q;
	memset(vis, 0, sizeof vis);
	q.push(u);
	vis[u] = true;
	while(!q.empty()) {
		u = q.front();
		q.pop();
		for(int v : g[u]) {
			if(vis[v]) continue;
			T2.emplace_back(u + 1, v + 1);
			vis[v] = true;
			q.push(v);
		}
	}
}

void solve() {
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0);
	bfs(0);
	for(auto [x, y] : T1) cout << x << ' ' << y << '\n';
	for(auto [x, y] : T2) cout << x << ' ' << y << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
