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

const int mod = 998244353, N = 1e5 + 100;

i64 fat[N], inv[N], invf[N], pt[N];

i64 C(int n, int k) {
	return fat[n] * invf[k] % mod * invf[n - k] % mod;
}

void solve() {
	int n;

	cin >> n;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
	for(int i = 2; i <= n; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		invf[i] = inv[i] * invf[i - 1] % mod;
	}

	pt[0] = 1;
	for(int i = 1; i <= n; ++i) pt[i] = inv[2] * pt[i - 1] % mod;

	vector<vector<int>> g(n);
	vector<int> sub(n, 0), cnt(n, 0), e(n, 0);

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	function<void(int, int)> dfs = [&](int u, int p) {
		sub[u] = cnt[u] = 1;
		e[u] = 0;
		for(int v : g[u]) {
			if(v == p) continue;
			dfs(v, u);
			sub[u] += sub[v];
			cnt[u] = (i64)cnt[v] * cnt[u] % mod;
			if(sub[v] % 2) ++e[u];
		}
		if(e[u] % 2 == 0) {
			i64 X = fat[e[u]] * pt[e[u] / 2] % mod * invf[e[u] / 2] % mod;
			cnt[u] = cnt[u] * X % mod;
		} else {
			i64 X = C(e[u], e[u] - 1) * fat[e[u] - 1] % mod * pt[e[u] / 2] % mod * invf[e[u] / 2] % mod;
			cnt[u] = cnt[u] * X % mod; 
		}
	};	

	dfs(0, 0);

	cout << cnt[0] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

