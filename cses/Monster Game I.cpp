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
 
	int n;
	
	cin >> n;
	
	vector<int> s(n + 1), f(n + 1);
	vector<i64> dp(n + 1);
	deque<pair<i64, i64>> st;
	
	cin >> f[0];
	
	for(int i = 1; i <= n; ++i) cin >> s[i];
	for(int i = 1; i <= n; ++i) cin >> f[i];
	
	st.emplace_back(f[0] + 0LL, 0LL);
	
	for(int i = 1; i <= n; ++i) {
			
		while((int)st.size() >= 2) {
			auto [x0, y0] = st[0];
			auto [x1, y1] = st[1];
			if(x0 * s[i] + y0 < x1 * s[i] + y1) break;
			st.pop_front();
		}
		
		auto [x, y] = st.front();
		dp[i] = x * s[i] + y;
	
		while((int)st.size() >= 2) {
			int n = st.size();
			
			auto [x1, y1] = st[n - 1];
			auto [x2, y2] = st[n - 2];
			
			ld m1 = (dp[i] - y1) / ld(x1 - f[i]);
			ld m2 = (y1 - y2) / ld(x2 - x1);
			
			if(m2 <= m1) break;
		
			st.pop_back();
		}
		
		st.emplace_back(f[i] + 0LL, dp[i]);
	}
	
	cout << dp[n] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
