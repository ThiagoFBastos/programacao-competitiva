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

const int N = 1e5 + 10;

vector<int> path, adj[N];
int n, c[N];

bool getpath(vector<int>& path, int u, int p) {
	path.pb(u);
	if(u == n - 1) return true;
	for(int v : adj[u]) {
		if(v == p) continue;
		else if(getpath(path, v, u)) return true;
	}
	path.pop_back();
	return false;
}

int dfs(int u, int p) {
	int n = 1;
	for(int v : adj[u]) {
		if(v == p || c[v] == 0) continue;
		n += dfs(v, u);
	}
	return n;
}

void solve() {
	cin >> n;

	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b); adj[b].pb(a);
	}

	memset(c, -1, sizeof c);
	getpath(path, 0, -1);

	for(int i = 0, m = path.size(); i < m; ++i) c[path[i]] = i < (m + 1) / 2;
	
	if(2 * dfs(0, -1) > n) cout << "Fennec\n";
	else cout << "Snuke\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

