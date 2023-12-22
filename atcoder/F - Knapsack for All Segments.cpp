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

const int mod = 998244353, N = 6e3 + 100;

i64 dp[N];

void solve() {

	int n, s;

	cin >> n >> s;

	i64 ans = 0;
	
	for(int i = 1; i <= n; ++i) {
		int a;

		cin >> a;

		if(a == s) ans = (ans + i * (n - i + 1ll)) % mod;
		if(a <= s) ans = (ans + dp[s - a] * (n - i + 1ll)) % mod;
		
		for(int j = s - a; j >= 0; --j) {
			dp[j + a] += dp[j];
			if(dp[a + j] >= mod) dp[a + j] -= mod;
		}

		dp[a] += i;

		if(dp[a] >= mod) dp[a] -= mod;	
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
