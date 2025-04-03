#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
const int N = 1e2;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long double p[N][N], dp[N + 1][N];
	int n, t, a, b, caso = 1;
	while(cin >> n >> a >> b >> t) {
		if(n == 0) break;
		long double P = 0;
		for(int k = 0; k < n; ++k)
			for(int i = 0; i < n; ++i)
				cin >> p[k][i];
		for(int k = 0; k <= t; ++k)
			for(int i = 0; i < n; ++i)
				dp[k][i] = 0;
		dp[0][a - 1] = 1.0;
		for(int i = 1; i <= t; ++i) {
			for(int k = 0; k < n; ++k) {
				if(k == b - 1) continue;
				for(int j = 0; j < n; ++j)
					dp[i][j] += p[k][j] * dp[i - 1][k];
			}
			P += dp[i][b - 1];
		}
		cout << "Instancia " << caso++ << '\n';
		cout << fixed << setprecision(6) << 1.0L - P << "\n\n";
	}
    return 0;
}