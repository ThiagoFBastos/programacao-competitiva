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
using i128 = __int128;

const int N = 1e5 + 10;

int dp[N][4], n;
vector<int> adj[N];

int DP(int u, int k) {
	if(dp[u][k] != -1) return dp[u][k];
	if(k == 0) {
		dp[u][k] = 0;
		for(int v : adj[u]) dp[u][k] += max(1 + DP(v, 2), DP(v, 3));
	} else if(k == 1) {
		array<int, 4> f[2];
		f[0].fill(-INF);
		f[0][0] = 0;
		for(int v : adj[u]) {
			f[1].fill(-INF);
			int a = DP(v, 0);
			int b = max(DP(v, 3), 1 + DP(v, 2));
			for(int i = 0; i < 4; ++i) {
				f[1][i] = max(f[1][i], f[0][i] + b);
				if(~i & 1) f[1][i|1] = max(f[1][i|1], f[0][i] + a);  
				if(~i & 2) f[1][i|2] = max(f[1][i|2], f[0][i] + a);
			}
			swap(f[0], f[1]);
		}
		dp[u][k] = f[0][3];
	} else if(k == 2) {
		array<int, 8> f[2];
		f[0].fill(-INF);
		f[0][0] = 0;
		for(int v : adj[u]) {
			f[1].fill(-INF);
			int a = DP(v, 0);
			int b = DP(v, 1);
			int c = max(DP(v, 3), 1 + DP(v, 2));
			for(int i = 0; i < 8; ++i) {
				f[1][i] = max(f[1][i], f[0][i] + c);
				if(~i & 1) f[1][i|1] = max(f[1][i|1], f[0][i] + a);  
				if(~i & 2) f[1][i|2] = max(f[1][i|2], f[0][i] + a);
				if(~i & 4) f[1][i|4] = max(f[1][i|4], f[0][i] + b);
			}
			swap(f[0], f[1]);
		}
		dp[u][k] = f[0][7];
	} else {
		dp[u][k] = 0;
		for(int v : adj[u]) dp[u][k] += max(1 + DP(v, 2), DP(v, 3));
	}
	return dp[u][k];
}

void solve() {
	cin >> n;

	for(int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		adj[p - 1].pb(i);
	}

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < 4; ++j)
			dp[i][j] = -1;
	
	cout << DP(0, 3) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
