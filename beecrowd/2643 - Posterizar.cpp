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

const int N = 257;
const i64 inf = 1e16L;

i64 dp[N][N], cost[N][N];

i64 sq(int x) {
	return (i64)x * x;
}

void solve() {
	
	int d, n;
	
	cin >> d >> n;
	
	vector<i64> cnt(256, 0);
	
	for(int i = 0; i < d; ++i) {
		int r;
		i64 p;
		cin >> r >> p;
		cnt[r] += p;
	}
	
	for(int i = 0; i <= 255; ++i)
	for(int j = 0; j <= n; ++j)
		dp[i][j] = inf;
		
	for(int i = 0; i <= 255; ++i)
		for(int j = i; j <= 255; ++j)
			for(int k = i; k < j; ++k) 
				cost[i][j] += cnt[k] * sq(min(k - i, j - k));
	
	for(int i = 0; i <= 255; ++i) {
		dp[i][1] = 0;
		for(int j = 0; j < i; ++j) dp[i][1] += cnt[j] * sq(i - j);
	}
	
	for(int i = 0; i <= 255; ++i)
		for(int j = i + 1; j <= 255; ++j)
			for(int k = 2; k <= n; ++k)
				dp[j][k] = min(dp[j][k], dp[i][k - 1] + cost[i][j]);
				
	i64 ans = inf;
	
	for(int i = 0; i <= 255; ++i) {
		i64 c = dp[i][n];
		for(int j = i; j <= 255; ++j) c += cnt[j] * sq(j - i);
		ans = min(ans, c);
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