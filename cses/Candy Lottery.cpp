#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ld dp[MAXN][MAXN];
	int n, k;
	cin >> n >> k;
	for(int i = 0; i < k; ++i)
		dp[0][i] = 1.0L / k;
	for(int i = 1; i < n; ++i)
		for(int j = 0; j < k; ++j)
			dp[i][j] = 0.0L;
	for(int i = 1; i < n; ++i) {
		for(int j = 0; j < k; ++j) {
			for(int h = 0; h <= j; ++h)
				dp[i][j] += dp[i - 1][h] / (ld)k;
			for(int h = 0; h < j; ++h)
				dp[i][j] += dp[i - 1][j] / (ld)k;
		}
	}
	ld ans = 0;
	for(int i = 1; i <= k; ++i)
		ans += i * dp[n - 1][i - 1];
	cout << fixed << setprecision(6) << ans << '\n';
	return 0;
} 
