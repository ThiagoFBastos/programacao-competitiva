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

const int N = 2e6;

int fac[N], g[N], dp[N];

void solve() {
	
	int n;

	cin >> n;

	g[1] = 1;

	for(int i = 2; i < N; ++i) {
		if(fac[i] == 0 && (i64)i * i < N) for(int k = i; k < N; k += i) fac[k] = i;
		if(!fac[i]) fac[i] = i;
		int k = i, j = 0;
		while(k % fac[i] == 0) k /= fac[i], ++j;
		g[i] = g[k] * (1 + j);
	}

	for(int i = N - 1; i; --i) {
		dp[i] = max(int(i == g[i]), dp[i]);
		dp[i - g[i]] = max(dp[i - g[i]], 1 + dp[i]);
		if(i == g[i] && dp[i] >= n) {
			vector<int> a(n + 1);
			a[0] = 0;
			for(int k = 1; k <= n; ++k) {
				a[k] = i;
				for(int j = 1; j <= 300; ++j) {
					if(g[i + j] == j && dp[i + j] >= n - k) {
						i += j;
						break;
					}
				}
			}
			for(int i = 1; i < n; ++i) cout << a[i] - a[i - 1] << ' ';
			cout << a[n] - a[n - 1] << '\n';
			break;
		}
	}

	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}