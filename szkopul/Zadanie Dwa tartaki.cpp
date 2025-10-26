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

const i64 inf = 1e10L;

double point(i64 a0, i64 b0, i64 a1, i64 b1) {
	return (b0 - b1) / double(a1 - a0);
}

void solve() {
	int n;
	
	cin >> n;
	
	vector<i64> D(n + 2, 0), W(n + 2, 0), WD(n + 2, 0), dp[2];
	i64 ans = inf;
	
	for(int i = 1; i <= n; ++i) {
		int w, d;
		cin >> w >> d;
		W[i] = W[i - 1] + w;
		WD[i] = WD[i - 1] + w * D[i - 1];
		D[i] = D[i - 1] + d;
	}
	
	W[n + 1] = W[n], WD[n + 1] = WD[n], D[n + 1] = D[n];
	
	for(int i = 0; i < 2; ++i) dp[i].assign(n + 2, inf);
	
	dp[0][0] = 0;
	
	for(int i = 1; i <= 3; ++i) {
		deque<pair<i64, i64>> st;
		
		st.emplace_back(0LL, dp[0][i - 1]);
		
		for(int j = 1; j <= n + 1; ++j) {
			i64 a = -W[j], b = dp[0][j] + WD[j];
			
			while((int)st.size() >= 2) {
				auto [a0, b0] = st[0];
				auto [a1, b1] = st[1];
				if(a0 * D[j - 1] + b0 < a1 * D[j - 1] + b1) break;
				st.pop_front();
			}
			
			auto [m, n] = st[0];
			
			dp[1][j] = m * D[j - 1] + n + D[j - 1] * W[j] - WD[j];
			
			while((int)st.size() >= 2) {
				int n = st.size();
				auto [a1, b1] = st[n - 1];
				auto [a2, b2] = st[n - 2];
				if(point(a, b, a1, b1) > point(a1, b1, a2, b2)) break;
				st.pop_back();	
			}
			
			st.emplace_back(a, b);
		}
		
		swap(dp[0], dp[1]);
		
		ans = min(ans, dp[0][n + 1]);
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
