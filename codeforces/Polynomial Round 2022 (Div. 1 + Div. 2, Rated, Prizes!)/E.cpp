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
using i128 = __int128;

const int N = 2e5 + 10;

int sub[2][N], n, d, m[2], depth[N], steps;
int where[2] = {0, 0};

vector<int> adj[N];

void dfssub(int u, int p) {
	for(int v : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfssub(v, u);
		sub[0][u] += sub[0][v];
		sub[1][u] += sub[1][v];
		steps += 2 * (sub[0][v] > 0);
		steps += 2 * (sub[1][v] > 0);
	}
}

vector<int> path {0};

void dfssteps(int u, int p) {
	for(int v : adj[u]) {
		if(v == p) continue;
		path.pb(v);
		int x = where[0], y = where[1];
		if(sub[0][v] && sub[1][v]) {
			where[0] = where[1] = path.size() - 1;
			dfssteps(v, u);
			where[0] = where[1] = x;
		} else if(sub[0][v]) {
			where[0] = path.size() - 1;
			if(where[1] >= (int)path.size() - 1) where[1] = path.size() - 2;
			int v1 = path[where[0]], v2 = path[where[1]];
			if(abs(depth[v1] - depth[v2]) > d) ++where[1], steps += 2;
			dfssteps(v, u);
			where[0] = x;
		} else if(sub[1][v]) {
			where[1] = path.size() - 1;
			if(where[0] >= (int)path.size() - 1) where[0] = path.size() - 2;	
			int v1 = path[where[0]], v2 = path[where[1]];
			if(abs(depth[v1] - depth[v2]) > d) ++where[0], steps += 2;
			dfssteps(v, u);
			where[1] = y;
		}
		path.pop_back();
	}
}

void solve() {
	cin >> n >> d;

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	for(int i = 0; i < 2; ++i) {
		cin >> m[i];
		for(int j = 0; j < m[i]; ++j) {
			int v;
			cin >> v;
			++sub[i][--v];
		}
	}

	dfssub(0, -1);
	dfssteps(0, -1);
	cout << steps << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
