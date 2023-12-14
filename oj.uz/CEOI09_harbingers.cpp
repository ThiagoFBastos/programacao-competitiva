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
 
const int N = 1e5 + 10;
 
vector<ii> adj[N];
int n, dist[N], s[N], vel[N], coords[N];
i64 dp[N];
 
int st[4 * N];
vector<ii> changes;
int cnt_changes;
 
i64 f(int k, int x) {
	i64 a = -dist[k], b = dp[k];
	return a * x + b;
}
 
void insert(int k, int l, int r, int p = 1) {
	int m = (l + r) / 2;
	bool v1 = f(k, coords[l]) < f(st[p], coords[l]);
	bool v2 = f(k, coords[m]) < f(st[p], coords[m]);
	if(v2) {
		changes.pb({p, st[p]});
		swap(st[p], k);
		++cnt_changes;
	}
	if(l == r) return;
	else if(v1 != v2) insert(k, l, m, 2 * p);
	else insert(k, m + 1, r, 2 * p + 1);
}
 
int insert(int k) {
	cnt_changes = 0;
	insert(k, 0, n - 1);
	return cnt_changes;
}
 
i64 get(int x, int l, int r, int p = 1) {
	i64 y = f(st[p], x);
	if(l == r) return y;
	int m = (l + r) / 2;
	i64 z = x <= coords[m] ? get(x, l, m, 2 * p) : get(x, m + 1, r, 2 * p + 1);
	return min(y, z);
}
 
void undo() {
	auto [p, f] = changes.back();
	st[p] = f;
	changes.pop_back();
}
 
void dfs(int u, int p) {
	int cnt = 0;
	if(u != p) {
		dp[u] = get(vel[u], 0, n - 1) + s[u] + (i64)dist[u] * vel[u];
		cnt = insert(u);
	}
	for(auto [v, l] : adj[u]) {
		if(v == p) continue;
		dist[v] = dist[u] + l;
		dfs(v, u);
	}
	while(cnt--) undo();
}
 
void solve() {
	cin >> n;
	for(int i = 1; i < n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}
	for(int i = 1; i < n; ++i) {
		cin >> s[i] >> vel[i];
		coords[i] = vel[i];
	}
	sort(coords, coords + n);
	dfs(0, 0);
	for(int i = 1; i < n; ++i) cout << dp[i] << ' ';
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
