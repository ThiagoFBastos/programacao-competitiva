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

const int N = 1e4 + 100, mod = 998244353;

i64 fat[N], inv[N], invf[N];

void solve() {
	
	string s;

	cin >> s;

	int n = s.size();

	for(int i = 0; i < 2; ++i) fat[i] = inv[i] = invf[i] = 1;

	for(int i = 2; i <= n; ++i) {
		fat[i] = i * fat[i - 1] % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		invf[i] = invf[i - 1] * inv[i] % mod;
	}

	vector<int> cnt(26, 0);
	for(char ch : s) ++cnt[ch - 'a'];
	
	vector<i64> dp(2 * n + 1, 0);
	i64 ans = 0;

	dp[0] = 1;

	for(int i = 0; i < 26; ++i) {
		for(int k = n; k >= 0; --k) {
			for(int j = 1; j <= cnt[i]; ++j) {
				i64 x = dp[k] * invf[j] % mod * fat[k + j] % mod * invf[k] % mod;
				dp[k + j] = (dp[k + j] + x) % mod;
			}
		}	
	}

	for(int i = 1; i <= n; ++i) ans = (ans + dp[i]) % mod;

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
