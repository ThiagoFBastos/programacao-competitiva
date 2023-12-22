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

const int N = 1e5 + 100;

const i64 inf = 1e16L;

i64 dp[3][N], v[N];

void solve() {
	
	int n;

	cin >> n;

	vector<int> a(n);

	for(int& v : a) cin >> v;

	for(int i = 0; i < 3; ++i)
	for(int j = 0; j <= n / 2; ++j)
		dp[i][j] = -inf;

	for(int i = 0; i < n; ++i) {

		int L = max(0, (i - 3) / 2 - 10), R = (i + 3) / 2;

		for(int j = L; j <= R; ++j) v[j] = -inf;

		for(int k = 2; k <= 3; ++k) {
			if(i - k < 0) break;
			for(int j = max(1, L); j <= R; ++j)
				v[j] = max(v[j], dp[(i - k) % 3][j - 1] + a[i]);
		}

		for(int j = L; j <= R; ++j) dp[i % 3][j] = v[j];

		dp[i % 3][1] = a[i];
	}

	i64 ans = -inf;

	for(int k = 1; k <= 3; ++k) {
		if(n - k < 0) break;
		ans = max(ans, dp[(n - k) % 3][n / 2]);
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

