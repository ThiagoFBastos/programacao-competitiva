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

const int mod = 998244353;

const int N = 6e3 + 100;

int dp[N];

void solve() {
	
	int n, s;

	cin >> n >> s;	

	dp[0] = 1;

	for(int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		for(int j = s; j >= 0; --j) {
			dp[a + j] += dp[j];
			if(dp[a + j] >= mod) dp[a + j] -= mod;
			dp[j] += dp[j];
			if(dp[j] >= mod) dp[j] -= mod;
		}
	}
	
	cout << dp[s] << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
