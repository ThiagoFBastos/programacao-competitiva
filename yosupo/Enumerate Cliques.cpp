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

const int MOD = 998244353, N = 128;

int x[N], n, m, ans;
bitset<N> adj[N], K;

void rec(int u, int t = 1) {	
	ans += t;
	if(ans >= MOD) ans -= MOD;
	for(int v = u + 1; v < n; ++v) {
		if((K & adj[v]).count() != K.count()) continue;
		K[v] = 1;
		rec(v, 1ll * t * x[v] % MOD);
		K[v] = 0;
	}
}

void solve() {
	cin >> n >> m;

	for(int i = 0; i < n; ++i) cin >> x[i];

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u][v] = adj[v][u] = 1;
	}

	rec(-1);

	cout << (ans + MOD - 1) % MOD << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}