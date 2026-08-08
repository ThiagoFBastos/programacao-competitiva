#pragma GCC optimize("O3")
#pragma GCC targe("mmx","sse","sse2","popcnt")

#include "bits/stdc++.h"

using namespace std;

int get_mask(string& s) {
	int mask = 0;
	for(int i = 0; i < int(size(s)); ++i) if(s[i] == '*') mask |= 1 << i;
	return mask;
}

int custo[1 << 10];

int cost(int mask, int n) {
	if(custo[mask] != -1) return custo[mask];
	int cnt = 0, p = 1;
	for(int j = 0; j < n; ++j) {
		if(mask & 1 << j) {
			cnt += p;
			p ^= 1;
		} else p = 1;
	}
	return custo[mask] = cnt;
}

const int INF = 1e9;

int dp[50][1 << 10];

void solve() {
	int n, m;
	cin >> n >> m;
	vector<string> g(n);
	memset(custo, -1, sizeof(int) << m);
	for(int i = 0; i < n; ++i) {
		cin >> g[i];
		for(int j = 0; j < (1 << m); ++j) dp[i][j] = INF;
	}
	int mask = get_mask(g[0]);
	for(int k = 0; k < (1 << m); ++k) if((mask & k) == k) dp[0][k] = cost(mask ^ k, m);
	for(int i = 1; i < n; ++i) {
		mask = get_mask(g[i]);
		for(int j = 0; j < (1 << m); ++j) {
			int cnt = __builtin_popcount(j), S = mask & ~j;
			for(int k = S; k; k = S & (k - 1)) dp[i][k] = min(dp[i][k], dp[i - 1][j] + cnt + cost(S ^ k, m));
			dp[i][0] = min(dp[i][0], dp[i - 1][j] + cnt + cost(S, m));
		}
	}
	cout << dp[n - 1][0] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}