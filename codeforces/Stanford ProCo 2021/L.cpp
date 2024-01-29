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

const int N = 2e5 + 10;

vector<int> adj[2][N], t;
vector<bool> vis;
int n, m;

void dfs(int u) {
	vis[u] = true;
	for(int v : adj[0][u]) {
		if(vis[v]) continue;
		dfs(v);
	}
	t.push_back(u);
}

void solve() {
	cin >> n >> m;

	vis.assign(n, false);
	vector<int> cnt_u(n, 0), cnt_d(n, 0), src(n, 1), sink(n, 1);
	int x = n, y = n, ans = 0;

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[0][a].push_back(b);
		adj[1][b].push_back(a);
		if(src[b]) --x;
		if(sink[a]) --y;
		src[b] = sink[a] = 0;
	}

	for(int i = 0; i < n; ++i) if(!vis[i]) dfs(i);

	fill(vis.begin(), vis.end(), false);

	for(int u : t) {
		cnt_u[u] = 1;
		for(int v : adj[0][u]) {
			if(vis[v]) continue;
			vis[v] = true;
			cnt_u[u] += cnt_u[v];
		}
	}

	fill(vis.begin(), vis.end(), false);
	reverse(t.begin(), t.end());

	for(int u : t) {
		cnt_d[u] = 1;
		for(int v : adj[1][u]) {
			if(vis[v]) continue;
			vis[v] = true;
			cnt_d[u] += cnt_d[v];
		}
	}

	for(int i = 0; i < n; ++i) ans += cnt_u[i] + cnt_d[i] - 1 == n;
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

