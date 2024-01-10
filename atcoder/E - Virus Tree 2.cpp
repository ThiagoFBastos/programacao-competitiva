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

const int mod = 1e9 + 7, N = 1e5 + 100;

i64 fat[N], inv[N], invf[N];

i64 P(int n, int k) {
	return fat[n] * invf[n - k] % mod;
}

void solve() {
	int n, k;
	
	cin >> n >> k;

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;
	for(int i = 2; i <= max(n, k); ++i) {
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		fat[i] = i * fat[i - 1] % mod;
		invf[i] = invf[i - 1] * inv[i] % mod;
	}

	vector<vector<int>> adj(n);	
	vector<int> cnt(n);

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(auto& v : adj) {
		if((int)v.size() > k) {
			cout << "0\n";
			return;
		}
	}

	function<void(int, int)> dfs = [&](int u, int p) {
		int ch = (int)adj[u].size() - (u != p);
		cnt[u] = u == p ? k * P(k - 1, ch) % mod : P(k - 2, ch);
		for(int v : adj[u]) {
			if(v == p) continue;
			dfs(v, u);
			cnt[u] = (i64)cnt[u] * cnt[v] % mod;
		}
	};

	dfs(0, 0);
	cout << cnt[0] << '\n';
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//cin >> t;
	while(t--) solve();
}
