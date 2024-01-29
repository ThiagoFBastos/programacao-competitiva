#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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

const int MOD = 1e9 + 7;

void solve() {
	int n, m;
	string s;

	cin >> n >> s;

	m = s.size();

	vector<i64> len(n);
	vector<int> ps(m + 1, 0);
	vector<tuple<int, i64, i64, i64>> query(n);
	vector<map<pair<i64,i64>, int>> dp(n);

	len[0] = m;
	for(int i = 1; i <= m; ++i) ps[i] = ps[i - 1] + s[i - 1];

	for(int i = 1; i < n; ++i) {
		string t;
		i64 x, y, lo, hi;
		cin >> t;	
		if(t == "SUB") {
			cin >> x >> lo >> hi;
			query[i] = {0, x, lo, hi - 1};
			len[i] = hi - lo;
		} else {
			cin >> x >> y;
			len[i] = len[x] + len[y];
			query[i] = {1, x, y, -1};
		}
	}

	auto dfs = [&](auto& self, int u, i64 l, i64 r) ->int {
		if(l > r) return 0;
		if(dp[u].count({l, r})) return dp[u][{l, r}];	
		else if(!u) return ps[r + 1] - ps[l];
		auto [t, a, b, c] = query[u];
		int cnt = 0;
		if(t == 0) cnt = self(self, a, max(l + b, b), min(r + b, c));
		else {
			cnt += self(self, a, l, min(len[a] - 1, r));
			cnt += self(self, b, max(len[a], l) - len[a], r - len[a]);
		}
		return dp[u][{l, r}] = cnt % MOD;
	};
	
	cout << dfs(dfs, n - 1, 0, len[n - 1] - 1) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

