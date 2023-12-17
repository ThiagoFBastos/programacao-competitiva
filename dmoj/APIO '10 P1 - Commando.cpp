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
	int n, a, b, c;
	
	cin >> n >> a >> b >> c;
	
	a = -a, b = -b, c = -c;
	
	vector<i64> dp(n + 1), pre(n + 1, 0);
	deque<pair<i64, i64>> ch;
	
	ch.emplace_back(0LL, 0LL);
	
	for(int i = 1; i <= n; ++i) {
		cin >> pre[i];
		
		pre[i] += pre[i - 1];
		
		while((int)ch.size() >= 2) {
			auto [a0, b0] = ch[0];
			auto [a1, b1] = ch[1];
			if(a0 * pre[i] + b0 < a1 * pre[i] + b1) break;
			ch.pop_front();
		}
		
		auto [m, n] = ch.front();
		
		dp[i] = c + pre[i] * (b + pre[i] * a) + n + m * pre[i];
		
		i64 a0 = -2 * a * pre[i], b0 = dp[i] + pre[i] * (a * pre[i] - b);
		
		while(ch.size() >= 2) {
			int n = ch.size();
			auto [a1, b1] = ch[n - 1];
			auto [a2, b2] = ch[n - 2];
			ld m1 = (b1 - b0) / ld(a0 - a1);
			ld m2 = (b2 - b1) / ld(a1 - a2);
			if(m1 >= m2) break;
			ch.pop_back();
		}
		
		ch.emplace_back(a0, b0); 
	}
	
	cout << -dp[n] << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
