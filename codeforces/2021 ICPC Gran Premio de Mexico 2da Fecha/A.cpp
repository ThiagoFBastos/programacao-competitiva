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

const int mod = 998244353;
int dp[1 << 14][15], g[1 << 14], e[1 << 14], p[256];

void solve() {
 	int n, m;
	cin >> n >> m;

	p[0] = 1;
	for(int i = 1; i <= m; ++i) p[i] = 2 * p[i - 1] % mod;

	vector<int> adj(n, 0);

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u] |= 1 << v;
		adj[v] |= 1 << u;
	}

	for(int i = 0; i < (1 << n); ++i) {
		int edges = 0, id = i & -i;
		for(int S = i; S; S -= S & -S) {
			int k = __builtin_ctz(S);
			edges += __builtin_popcount(i & adj[k]);
		}
		e[i] = edges /= 2;
		g[i] = p[e[i]];
		for(int S = i & (i - 1); S; S = (S - 1) & i) {
			if(~S & id) continue;
			g[i] -= (i64)g[S] * p[e[i ^ S]] % mod;
			if(g[i] < 0) g[i] += mod;
		}
	}
  
  dp[0][0] = 1;
  for(int i = 0; i < (1 << n); ++i) {
    int id = i & -i;
    for(int k = 1; k <= n; ++k) {
      for(int S = i; S; S = (S - 1) & i) {
        if(~S & id) continue;
        dp[i][k] += (i64)g[S] * dp[i ^ S][k - 1] % mod;
        if(dp[i][k] >= mod) dp[i][k] -= mod;
      }
    }
  }
  
  for(int i = 1; i <= n; ++i) cout << dp[(1 << n) - 1][i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


