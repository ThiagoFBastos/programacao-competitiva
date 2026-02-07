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

const int N = 1e5 + 100, MOD = 998244353;

int deg[N], x[N], n, m, ans;
vector<int> adj[N];
unordered_set<int> edges[N], heavy[N];

i64 exp(i64 n, int p) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % MOD;
		n = n * n % MOD;
	}
	return ans;
}

void solve() {
	cin >> n >> m;

	for(int i = 0; i < n; ++i) cin >> x[i];

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
		++deg[u], ++deg[v];
	}

	for(int i = 0; i < n; ++i) {
		edges[i].reserve(deg[i]);
		for(int j : adj[i]) edges[i].insert(j);
	}

	for(int i = 0; i < n; ++i) {
		auto& A = adj[i];

		for(int j : A) if(1ll * deg[j] * deg[j] > n) heavy[i].insert(j);

		if(1ll * deg[i] * deg[i] > n) continue;
		
		int sum = 0;

		for(int k = 0; k < (int)A.size(); ++k) {
			i64 parcial = 0;
			int u = A[k];
			for(int j = k + 1; j < (int)A.size(); ++j) {
				int v = A[j];
				if(!edges[u].count(v)) continue;
				parcial += x[v];
			}
			parcial %= MOD;
			sum = (sum + parcial * x[u]) % MOD;
		}

		ans = (ans + 1ll * x[i] * sum) % MOD;
	}

	for(int i = 0; i < n; ++i) {
		int parcial = 0;
		for(int k : heavy[i]) {
			i64 sum = 0;
			for(int j : adj[i]) {
				if(j < i || !heavy[j].count(k)) continue;	
				sum += x[j];
			}
			sum %= MOD;
			parcial = (parcial + x[k] * sum) % MOD;
		}
		ans = (ans + 1ll * parcial * x[i]) % MOD;
	}

	cout << ans * exp(3, MOD - 2) % MOD << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}