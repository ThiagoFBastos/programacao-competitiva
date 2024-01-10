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

void solve() {
	int n, m;
	cin >> n >> m;

	vector<vector<ii>> a(n);
	vector<i64> dp(1 << n, 0);

	for(int i = 0; i < m; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		a[x - 1].emplace_back(y, z);
	}

	dp.back() = 1;
	
	for(int i = (1 << n) - 1; i >= 0; --i) {
		int k = n - __builtin_popcount(i);

		for(int j = 0; j < n; ++j) {
			if(i & 1 << j) {				
				int S = ((1 << n) - 1) & ~(i ^ (1 << j));
				if(a[k].empty()) dp[i ^ (1 << j)] += dp[i];
				else {
					bool ok = true;
					for(auto [x, y] : a[k]) ok = ok && __builtin_popcount(S & ((1 << x) - 1)) <= y;
					if(ok) dp[i ^ (1 << j)] += dp[i];
				}
			}
		}
	}

	cout << dp[0] << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

