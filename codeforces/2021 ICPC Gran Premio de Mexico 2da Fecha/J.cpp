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
	const int INF = 2e9;
	int A, T;
	cin >> A >> T;
	map<int, vector<ii>> S;
	vector<int> dp(T + 1, -INF);
	for(int i = 0; i < A; ++i) {
		int h, d, t;
		cin >> h >> d >> t;
		while(t--) {
			int x;
			cin >> x;
			S[x].emplace_back(h, d);
		}
	}
	int ans = 0;
	dp[0] = 0;
	for(int i = 0; i <= T; ++i) {
		if(i) dp[i] = max(dp[i], dp[i - 1]);
		ans = max(ans, dp[i]);
		if(!S.count(i)) continue;
		auto& a = S[i];
		for(auto [h, d] : a)
			dp[min(i + d, T)] = max(dp[min(i + d, T)], dp[i] + h);
	}
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


