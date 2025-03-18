#include "bits/stdc++.h"

using namespace std;

#define INF    1000000000
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

const int N = 2e5 + 10, MOD = 1e9 + 7;

vector<int> adj[N];
int depth[N], max_depth[N], n, ans;

i64 exp(i64 n, int p, int mod) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}

void dfs(int u, int p) {
	max_depth[u] = depth[u];
	for(int v : adj[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfs(v, u);
		max_depth[u] = max(max_depth[u], max_depth[v]);
	}
	ans = (ans + exp(2, n - 1, MOD) * (max_depth[u] - depth[u] + 1)) % MOD;
}

void solve() {
	cin >> n;

	for(int i = 0; i < n; ++i) adj[i].clear();

	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	ans = 0;
	dfs(0, -1);
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
