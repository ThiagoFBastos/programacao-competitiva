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

const int N = 2e5 + 10;

vector<int> adj[N];
int min_dist[N], is_bad[N], bad;

void dfs(int u, int p, int len) {
	int d[2] = {INF, INF};
	min_dist[u] = INF;
	if((int)adj[u].size() == 1) min_dist[u] = 0;
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u, len);
		if(d[0] > min_dist[v] + 1) d[1] = d[0], d[0] = min_dist[v] + 1;
		else d[1] = min(d[1], min_dist[v] + 1); 
		min_dist[u] = min(min_dist[u], min_dist[v] + 1);
	}
	is_bad[u] = max(d[0], d[1]) < len && d[0] + d[1] < 2 * len - 1;
	bad += is_bad[u];
}

bool can(int u, int p, int len) {
	int d[3] = {INF, INF, INF};

	for(int v : adj[u]) {
		if(d[0] > min_dist[v] + 1) d[2] = d[1], d[1] = d[0], d[0] = min_dist[v] + 1;
		else if(d[1] > min_dist[v] + 1) d[2] = d[1], d[1] = min_dist[v] + 1;
		else d[2] = min(d[2], min_dist[v] + 1);
	}

	bad += (max(d[0], d[1]) < len && d[0] + d[1] < 2 * len - 1) - is_bad[u];

	if(d[0] >= len - 1 && !bad) return true;

	for(int v : adj[u]) {
		if(v == p) continue;
		int s[3];
		
		s[0] = min_dist[u];
		s[1] = min_dist[v];
		s[2] = bad;

		bad -= max(d[0], d[1]) < len && d[0] + d[1] < 2 * len - 1;

		if(min_dist[v] + 1 == d[0]) {
			bad += max(d[1], d[2]) < len && d[1] + d[2] < 2 * len - 1;
			min_dist[u] = min(d[1], (int)adj[u].size() == 1 ? 0 : INF);
		} else if(min_dist[v] + 1 == d[1]) {
			bad += max(d[0], d[2]) < len && d[0] + d[2] < 2 * len - 1;
			min_dist[u] = min(d[0], (int)adj[u].size() == 1 ? 0 : INF);
		} else {
			bad += max(d[0], d[1]) < len && d[0] + d[1] < 2 * len - 1;
			min_dist[u] = min(d[0], (int)adj[u].size() == 1 ? 0 : INF);
		}

		min_dist[v] = min(min_dist[v], min_dist[u] + 1);

		if(can(v, u, len)) return true;

		min_dist[u] = s[0];
		min_dist[v] = s[1];
		bad = s[2];
	}

	return false;
}

void solve() {
	int n;

	cin >> n;

	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	int lo = 1, hi = n + 1;

	while(lo < hi) {
		int m = (lo + hi) / 2;
		bad = 0;
		dfs(0, -1, m);
		if(!can(0, -1, m)) hi = m;
		else lo = m + 1;
	}

	cout << hi - 1 << '\n';

	for(int i = 0; i < n; ++i) adj[i].clear();
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
