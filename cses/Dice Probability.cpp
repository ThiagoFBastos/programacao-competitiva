#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, a, b;
	ld dp[101][601];
	cin >> n >> a >> b;
	for(int k = 1; k <= n; ++k)
		for(int i = k; i <= 6 * k; ++i)
			dp[k][i] = 0;
	dp[0][0] = 1.0;
	for(int k = 1; k <= n; ++k) {
		int s = k - 1, t = 6 * (k - 1);
		while(s <= t) {
			for(int i = 1; i <= 6; ++i)
				dp[k][s + i] += dp[k - 1][s] / 6.0L;
			++s;
		}
	}
	ld p = 0;
	while(a <= b) {
		p += dp[n][a];
		++a;
	}
 	cout << fixed << setprecision(6) << p << '\n';
	return 0;
} 
