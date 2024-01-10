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

const int mod = 1e9 + 7;

int n;
vector<vector<pair<int, i64>>> g;
vector<array<int, 2>> XOR;
i64 cnt;

void dfs(int u, int p, int bit) {
	XOR[u].fill(0);
	XOR[u][0] = 1;
	for(auto [v, w] : g[u]) {
		if(v == p) continue;
		dfs(v, u, bit);
		int b = !!(w & 1LL << bit);
		for(int k = 0; k < 2; ++k) cnt = (cnt + (i64)XOR[u][k ^ b ^ 1] * XOR[v][k]) % mod;
		for(int k = 0; k < 2; ++k) XOR[u][k ^ b] += XOR[v][k];
	}
}

void solve() {	

	cin >> n;	

	g.resize(n);
	XOR.resize(n);

	for(int i = 0; i < n - 1; ++i) {
		int u, v; 
		i64 w;
		cin >> u >> v >> w;
		--u, --v;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	
	i64 sum = 0;
	for(int i = 0; i < 60; ++i) {
		cnt = 0;
		dfs(0, 0, i);
		sum = (sum + (1LL << i) % mod * cnt) % mod;
	}

	cout << sum << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

