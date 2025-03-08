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

double intersect(i64 a0, i64 b0, i64 a1, i64 b1) {
	return (b1 - b0) / double(a0 - a1);
}

void solve() {
	int n;
	
	cin >> n;
	
	vector<i64> x(n + 1), dp(n + 1), c(n + 1);
	deque<pair<i64, i64>> st;
	
	for(int i = 1; i <= n; ++i) cin >> x[i] >> c[i];
	
	st.emplace_back(0LL, 0LL);
	
	for(int i = 1; i <= n; ++i) {
	
		while(st.size() >= 2) {
			auto [a0, b0] = st[0];
			auto [a1, b1] = st[1];
			if(a0 * x[i] + b0 > a1 * x[i] + b1) break;
			st.pop_front();
		}
		
		auto [a, b] = st.front();
		
		dp[i] = a * x[i] + b - c[i];
		
		i64 a0 = x[i], b0 = dp[i] - x[i] * x[i];
		
		while(st.size() >= 2) {
			int n = st.size();
			auto [a1, b1] = st[n - 1];
			auto [a2, b2] = st[n - 2];
			if(intersect(a0, b0, a1, b1) > intersect(a1, b1, a2, b2)) break;
			st.pop_back();
		}
		
		st.emplace_back(a0, b0);
	}
	
	if(dp[n] <= 0) cout << "Perde ";
	else cout << "Ganha ";
	
	cout << abs(dp[n]) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}