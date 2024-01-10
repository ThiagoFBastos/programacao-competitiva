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

const int N = 1e5 + 1000, mod = 998244353;
int dp[N];

void solve() {
	int n, m, k;
	
	cin >> n >> m >> k;	
	
	vector<int> a(m), cnt(n, 0), pts(n);
	vector<ii> p(n);
	vector<vector<ii>> g(n);
	
	for(int& v : a) {
		cin >> v;
		--v;
	}
	
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].emplace_back(v, i - 1);
		g[v].emplace_back(u, i - 1);
	}
	
	for(int i = 0; i < m - 1; ++i) {
		queue<int> q;
		fill(p.begin(), p.end(), make_pair(-1, -1));
		p[a[i]] = make_pair(a[i], 0);
		q.push(a[i]);
		while(!q.empty()) {
			int v = q.front();
			q.pop();
			if(v == a[i + 1]) break;
			for(auto [u, e] : g[v]) {
				if(p[u].first != -1) continue;
				p[u] = make_pair(v, e);
				q.push(u);
			}
		}
		for(int v = a[i + 1]; v != a[i]; v = p[v].first) ++cnt[p[v].second];
	}
	
	int s = 0, z = 0, ans = 0;
	
	for(int i = 0; i < n - 1; ++i) {
		s += cnt[i];
		if(!cnt[i]) ++z;
	}
	
	dp[0] = 1;
	
	for(int i = 0; i < n; ++i) {
		if(cnt[i] == 0) continue;
		for(int j = s; j >= 0; --j) {
			int k = j + cnt[i];
			dp[k] += dp[j];
			if(dp[k] >= mod) dp[k] -= mod;
		}
	}
	
	pts[0] = 1;
	for(int k = 1; k < n; ++k) {
		pts[k] = pts[k - 1] << 1;
		if(pts[k] >= mod) pts[k] -= mod;
	}

	for(int i = 0; i <= s; ++i) {
		int j = s - i;
		if(i - j == k) {
			ans += dp[i];
			if(ans >= mod) ans -= mod;
		}
	}
	
	cout << (i64)ans * pts[z] % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
