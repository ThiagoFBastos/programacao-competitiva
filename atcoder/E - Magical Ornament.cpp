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

const int inf = 1e9;

int dp[1 << 17][17];

void solve() {
	
	int n, m, k;

	cin >> n >> m;

	vector<vector<int>> g(n);
	
	while(m--) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}	

	cin >> k;

	vector<int> c(k);
	array<array<int, 17>, 17> d;

	for(int& v : c) {
		cin >> v;
		--v;
	}

	for(int i = 0; i < k; ++i) {
		vector<int> dist(n, -1);
		queue<int> q;
		dist[c[i]] = 0;
		q.push(c[i]);
		d[i].fill(-1);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int v : g[u]) {
				if(dist[v] != -1) continue;
				dist[v] = 1 + dist[u];
				q.push(v);
			}
		}
		for(int j = 0; j < k; ++j) d[i][j] = dist[c[j]];
	}

	for(int i = 0; i < (1 << k); ++i)
	for(int j = 0; j < k; ++j)
		dp[i][j] = inf;

	for(int i = 0; i < k; ++i) dp[1 << i][i] = 1;

	for(int i = 1; i < (1 << k); ++i) {
		if((i & (i - 1)) == 0) continue;
		for(int A = i; A; A -= A & -A) {
			int u = __builtin_ctz(A);
			for(int B = i ^ (1 << u); B; B -= B & -B) {
				int v = __builtin_ctz(B);
				if(d[v][u] == -1) continue;
				dp[i][u] = min(dp[i][u], dp[i ^ (1 << u)][v] + d[v][u]);
			}
		}
	}

	int ans = inf;
	for(int i = 0; i < k; ++i) ans = min(ans, dp[(1 << k) - 1][i]);
	if(ans == inf) ans = -1;
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

