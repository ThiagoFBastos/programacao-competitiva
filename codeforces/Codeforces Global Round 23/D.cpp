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

const int N = 2e5 + 100;

vector<int> adj[N];
int s[N], n, k;
map<int, i64> dp[N];
set<int> K[N];

void dfs(int u) {
	int deg = adj[u].size();

	for(int v : adj[u]) {
		for(int x : K[u]) {
			K[v].insert(x / deg);
			K[v].insert((x + deg - 1) / deg);
		}
		dfs(v);
	}

	for(int x : K[u]) {
		i64 ans = 0;	

		if(deg) {
			vector<i64> z;

			for(int v : adj[u]) {
				auto it = dp[v].find((x + deg - 1) / deg);
				i64 ret = 0;
				if(it != dp[v].end()) {
					ret = it->second;
					ans += it->second;
				}
				auto it2 = dp[v].find(x / deg);
				if(it2 != dp[v].end()) z.pb(it2->second - ret);
			}
			
			sort(rall(z));

			int m = deg - x % deg;

			for(int i = 0; i < m; ++i) ans += z[i];
		}

		dp[u][x] = ans + (i64)x * s[u];
	}
}

void solve() {
	cin >> n >> k;

	for(int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		adj[p - 1].pb(i);
	}

	for(int i = 0; i < n; ++i) cin >> s[i];

	K[0] = {k};
	dfs(0);
	cout << dp[0][k] << '\n';

	for(int i = 0; i < n; ++i) {
		adj[i].clear();
		K[i].clear();
		dp[i].clear();
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
