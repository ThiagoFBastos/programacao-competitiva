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

const int N = 1e5 + 1, mod = 1e9 + 7;

i64 exp(i64 n, int k) {
	i64 ans = 1;
	for(; k > 0; k >>= 1) {
		if(k & 1) ans = n * ans % mod;
		n = n * n % mod;
	}
	return ans;
}

void solve() {
	int n, k;

	cin >> n >> k;

	vector<i64> cnt(k + 1);
	i64 ans = 0;

	for(int i = 1; i <= k; ++i) cnt[i] = exp(k / i, n);
		
	for(int i = k; i > 0; --i) {
		for(int j = 2 * i; j <= k; j += i) {
			cnt[i] -= cnt[j];
			if(cnt[i] < 0) cnt[i] += mod;
		}

		ans = (ans + i * cnt[i]) % mod;
	}

	cout << (ans + mod) % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

