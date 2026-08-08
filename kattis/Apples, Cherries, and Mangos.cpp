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

const int mod = 1e9 + 7, N = 4e5 + 100;

i64 cnt[N], fat[N], inv[N], invf[N];

i64 C(int n, int k) {
	return fat[n] * invf[k] % mod * invf[n - k] % mod;
}

void solve() {
	
	int a, c, m;
	i64 ans = 0;

	cin >> a >> c >> m;

	if(m < max(a, c)) {
		if(a < c) swap(a, m);
		else swap(c, m);
	}

	if(m - 1 > a + c) {
		cout << "0\n";
		return;
	}

	
	for(int k = 0; k < 2; ++k) fat[k] = inv[k] = invf[k] = 1;

	for(int k = 2; k < N; ++k) {
		fat[k] = k * fat[k - 1] % mod;
		inv[k] = (mod - mod / k) * inv[mod % k] % mod;
		invf[k] = invf[k - 1] * inv[k] % mod;
	}

	for(int k = 2; k <= a + c; ++k) {
		int g = k / 2;
		if(k & 1) {
			if(g + 1 <= a && g <= c) 
				cnt[k] = C(a - 1, a - g - 1) * C(c - 1, c - g) % mod;
			if(g <= a && g + 1 <= c)
				cnt[k] = (cnt[k] + C(a - 1, a - g) * C(c - 1, c - g - 1)) % mod;
		} else if(g <= min(a, c)) 
			cnt[k] = 2 * C(a - 1, a - g) * C(c - 1, c - g) % mod;
	}


	for(int i = 2; i <= a + c; ++i) {
		int adj = a + c - i;
		if(adj > m) continue;
		i64 ways = fat[a + c + 1 - adj] * invf[a + c + 1 - m] % mod * invf[m - adj] % mod;
		ans = (ans + cnt[i] * ways) % mod;
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