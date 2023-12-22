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

const int N = 2e5 + 100, mod = 1e9 + 7;

i64 fat[N], inv[N], invf[N];

int n;
vector<vector<int>> g;
vector<i64> cnt, ans;
vector<int> sz;

void pre(int u, int p) {
	cnt[u] = sz[u] = 1;
	for(int v : g[u]) {
		if(v == p) continue;
		pre(v, u);
		cnt[u] = cnt[u] * invf[sz[v]] % mod * cnt[v] % mod;
		sz[u] += sz[v];
	}
	cnt[u] = cnt[u] * fat[sz[u] - 1] % mod;
}

i64 exp(i64 n, int p, int mod) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}

void dfs(int u, int p) {
	ans[u] = cnt[u];

	for(int v : g[u]) {
		if(v == p) continue;
		i64 x = cnt[u], y = cnt[v];
		
		cnt[u] = cnt[u] * invf[n - 1] % mod;
		cnt[u] = cnt[u] * fat[n - sz[v] - 1] % mod;
		cnt[u] = cnt[u] * fat[sz[v]] % mod;
		cnt[u] = cnt[u] * exp(cnt[v], mod - 2, mod) % mod;
		
		cnt[v] = cnt[v] * invf[sz[v] - 1] % mod;
		cnt[v] = cnt[v] * fat[n - 1] % mod;
		cnt[v] = cnt[v] * invf[n - sz[v]] % mod;
		cnt[v] = cnt[v] * cnt[u] % mod;

		dfs(v, u);

		cnt[u] = x, cnt[v] = y;
	}
}


void solve() {
	cin >> n;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
	for(int i = 2; i <= n; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		invf[i] = invf[i - 1] * inv[i] % mod;
	}

	g.resize(n);
	cnt.resize(n);
	sz.resize(n);
	ans.resize(n);

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	pre(0, 0);
	dfs(0, 0);

	for(i64 v : ans) cout << v << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
