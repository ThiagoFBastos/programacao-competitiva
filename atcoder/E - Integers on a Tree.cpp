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

const int N = 1e5 + 100;

vector<int> adj[N];
int c[N], l[N], r[N], n, k;

void dfs(int u, int p) {
	l[u] = -INF;
	r[u] = INF;
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u);
		l[u] = max(l[u], l[v] - 1);
		r[u] = min(r[u], r[v] + 1);
	}
	if(c[u] != -1) l[u] = r[u] = c[u];
}

void dfs(int u, int p, int x) {
	if(c[u] == -1) {
		if(x - 1 >= l[u] && x - 1 <= r[u]) c[u] = x - 1;
		else c[u] = x + 1;
	}
	for(int v : adj[u]) {
		if(v == p) continue;
		dfs(v, u, c[u]);
	}
}

void solve() {
	cin >> n;

	memset(c, -1, sizeof c);

	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	cin >> k;

	int r = -1;

	while(k--) {
		int v;
		cin >> v;
		--v;
		cin >> c[v];
		r = v;
	}

	dfs(r, -1);
	dfs(r, -1, c[r]);
	
	for(int u = 0; u < n; ++u) {
		for(int v : adj[u]) {
			if(abs(c[u] - c[v]) != 1) {
				cout << "No\n";
				return;
			}
		}
	}

	cout << "Yes\n";
	for(int i = 0; i < n; ++i) cout << c[i] << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
