#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
#define f first
#define s second
#define ri register int
typedef long long ll;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
const int N = 1000, M = 6000;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ld **dp, **p;
	int n, v;
	dp = new ld*[N + 1];
	p = new ld*[N + 1];
	for(ri k = 0; k <= N; ++k) {
		dp[k] = new ld[M + 1];
		p[k] = new ld[M + 1];
		for(ri i = 0; i <= M; ++i)
			dp[k][i] = p[k][i] = 0;
	}
	dp[0][0] = 1.0;
	for(ri k = 1; k <= N; ++k) {
		int a = k - 1, b = 6 * k;
		for(ri i = 1; i <= 6; ++i)
			for(ri j = a; i + j <= b; ++j)
				dp[k][j + i] += dp[k - 1][j] / 6.0L;
	}
	for(ri k = 1; k <= N; ++k) {
		int m = 6 * k;
		for(ri i = 1; i <= m; ++i)
			p[k][i] = p[k][i - 1] + dp[k][i];
	}
	while(cin >> n >> v)
		cout << fixed << setprecision(4) << (v <= 6 * n ? p[n][6 * n] - p[n][max(v - 1, 0)] : 0) << '\n';
	return 0;
}