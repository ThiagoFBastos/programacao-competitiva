#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
typedef long long ll;
typedef long double ld;
using namespace std;
using vi = vector<int>;
int main() {
	ios_base :: sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	ld dp[1 << 16], d[16][16];
	int t, p[16][2];
	cin >> t;
	while(t--) {
		int n, m;
		cin >> n;
		for(int k = 0; k < n; ++k) cin >> p[k][0] >> p[k][1];
		for(int k = 0; k < n; ++k)
			for(int i = k + 1; i < n; ++i)
				d[k][i] = d[i][k] = hypot(p[k][0] - p[i][0], p[k][1] - p[i][1]);
		dp[0] = 0;
		m = 1 << n;
		for(int k = 1; k < m; ++k) {
			int s = 1;
			dp[k] = INT_MAX;
			for(int i = 0; i < n; ++i) {
				if(k & s) {
					int r = 1, mask = k ^ s;
					for(int j = 0; j < n; ++j) {
						if(mask & r)
							dp[k] = min(dp[k], d[i][j] + dp[mask ^ r]);
						r <<= 1;
					}
				}
				s <<= 1;
			}
		}
		cout << fixed << setprecision(2) << dp[m - 1] << '\n';
	}
	return 0;
}