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

using edge = tuple<int, int, int>;
using T = tuple<i64, int, int>;

const int N = 50, K = 2501;

i64 dp[N][K];

void solve() {
	
	int n, m, s;
	
	cin >> n >> m >> s;
	
	s = min(s, 50 * n);
	
	vector<vector<edge>> g(n);
	priority_queue<T> pq;
	vector<ii> sw(n);
	vector<i64> tim(n, LLONG_MAX);
	
	for(int i = 0; i < m; ++i) {
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		--u, --v;
		g[u].emplace_back(v, a, b);
		g[v].emplace_back(u, a, b);
	}
	
	for(auto &[c, d] : sw) cin >> c >> d;
	
	for(int i = 0; i < n; ++i)
	for(int j = 0; j <= 50 * n; ++j)
		dp[i][j] = -1;
		
	pq.emplace(0LL, s, 0);
	
	while(!pq.empty()) {
		auto [t, coins, u] = pq.top();
		pq.pop();
		
		t = -t;
		
		if(dp[u][coins] != -1) continue;
		
		tim[u] = min(tim[u], t);
		dp[u][coins] = t;
		
		for(auto [v, pay, tim] : g[u]) {	
			if(coins - pay >= 0 && dp[v][coins - pay] == -1)
				pq.emplace(-t - tim, coins - pay, v);
		}
		
		int c = min(50 * n, coins + sw[u].first);
		if(dp[u][c] == -1) pq.emplace(-t - sw[u].second, c, u);
	}
	
	for(int i = 1; i < n; ++i) cout << tim[i] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

