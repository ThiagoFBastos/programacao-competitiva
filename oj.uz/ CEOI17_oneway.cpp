#include <bits/stdc++.h>
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
const int N = 1e5 + 100;
 
int n, m, q, in[N], out[N], low[N], t, dir[N];
 
bool flag[N];
vector<tuple<int, int, int>> g[N];
 
vector<int> to[N], from[N];
ii mi[N], ma[N];
 
void preProcess(int u, int p = -1) {
	in[u] = out[u] = t++;
	for(auto [v, e, f] : g[u]) {
		if(in[v] < 0) {
			preProcess(v, u);
			out[u] = out[v];
		}
	}
}
 
void dfs(int u, int p = -1) {
	low[u] = t++;
 
	mi[u] = ii(n, -1);
	ma[u] = ii(-1, -1);
 
	for(auto [v, e, f] : g[u]) {
		if(low[v] < 0) {
			dfs(v, u);
          
			mi[u] = min(mi[u], mi[v]);
			ma[u] = max(ma[u], ma[v]);
 
			if(low[v] > in[u]) {
				if(mi[v].first < in[v]) {
					auto [t, ff] = mi[v];
					dir[e] = f * ff;
				}
				if(ma[v].first > out[v]) {
					auto [t, ff] = ma[v];
					dir[e] = f * ff;
				}
			}
 
			low[u] = min(low[u], low[v]);
		} else {
			if(!(v == p && !flag[u])) low[u] = min(low[u], in[v]); 
			if(v == p) flag[u] = true;
		}
	}
	
	for(int v : to[u]) {
		mi[u] = min(mi[u], ii(in[v], -1));
		ma[u] = max(ma[u], ii(in[v], -1));
	}
 
	for(int v : from[u]) {
		mi[u] = min(mi[u], ii(in[v], 1));
		ma[u] = max(ma[u], ii(in[v], 1));
	}
}
 
void solve() {
	cin >> n >> m;
 
	memset(in, -1, sizeof(int) * n);
	memset(low, -1, sizeof(int) * n);
 
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		if(u != v) {
			g[u].emplace_back(v, i, 1);
			g[v].emplace_back(u, i, -1);
		}
	}
 
	cin >> q;
 
	while(q--) {
		int x, y;
		cin >> x >> y;
		--x, --y;
		to[x].push_back(y);
		from[y].push_back(x);
	}
 
	for(int i = 0; i < n; ++i) if(in[i] < 0) preProcess(i);
	t = 0;
	for(int i = 0; i < n; ++i) if(low[i] < 0) dfs(i);
 
	string ans;
 
	for(int i = 0; i < m; ++i) {
		if(dir[i] == -1) ans += 'L';
		else if(dir[i] == 1) ans += 'R';
		else ans += 'B';
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
