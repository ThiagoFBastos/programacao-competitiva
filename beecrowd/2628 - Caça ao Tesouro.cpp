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

const int N = 1e5 + 1, inf = 1e9;

bitset<N> is_prime;

int dist[16][16], dp[1 << 15][15];

void solve() {
	int n, e;

	cin >> n >> e;

	if(cin.eof()) exit(0);

	vector<int> s, d(n + 1);
	vector<vector<ii>> g(n + 1);

	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		if(is_prime[x]) s.push_back(i);
	}

	s.push_back(n);

	for(int i = 0; i < e; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}

	for(int i = 0; i < (int)s.size(); ++i) {
		fill(d.begin(), d.end(), -1);

		priority_queue<ii> pq;

		pq.push({0, s[i]});

		while(!pq.empty()) {
			auto [c, v] = pq.top();
			pq.pop();
			c *= -1;
			if(d[v] != -1) continue;
			d[v] = c;
			for(auto [u, w] : g[v]) {
				if(d[u] != -1) continue;
				pq.push({-c - w, u});
			}
		}

		for(int j = 0; j < (int)s.size(); ++j) dist[i][j] = d[s[j]];
	}

	int m = s.size(), ans = inf;

	for(int i = 0; i < (1 << (m - 1)); ++i)
	for(int j = 0; j < m - 1; ++j)
		dp[i][j] = inf;

	for(int i = 0; i < m - 1; ++i) dp[1 << i][i] = dist[m - 1][i];

	for(int i = 1; i < (1 << (m - 1)); ++i) {
		for(int k = i; k > 0; k -= k & -k) {
			int x = __builtin_ctz(k);
			for(int j = i ^ (1 << x); j > 0; j -= j & -j) {
				int y = __builtin_ctz(j);
				dp[i][y] = min(dp[i][y], dp[i ^ (1 << y)][x] + dist[x][y]);
			}
		}
	}

	for(int i = 0; i < m - 1; ++i) ans = min(ans, dist[m - 1][i] + dp[(1 << (m - 1)) - 1][i]);
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	is_prime.set();
	is_prime[1] = 0;

	for(int k = 2; k * k < N; ++k) {
		if(!is_prime[k]) continue;
		for(int j = k * k; j < N; j += k) is_prime[j] = 0;
	}
	
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}