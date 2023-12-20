#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
#define f first
#define s second
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 500
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	unsigned dp[MAXN + 1][MAXN + 1];
	int a, b;
	cin >> a >> b;
	for(int i = 0; i <= a; ++i)
		for(int j = 0; j <= b; ++j)
			dp[i][j] = INT_MAX;
	for(int i = 0; i <= min(a, b); ++i)
		dp[i][i] = 0;
	for(int k = 1; k <= a; ++k) {
		for(int j = 1; j <= b; ++j) {
			for(int i = 1; i <= k; ++i)
				dp[k][j] = min(dp[k][j], 1 + dp[k - i][j] + dp[i][j]);
			for(int i = 1; i <= j; ++i)
				dp[k][j] = min(dp[k][j], 1 + dp[k][j - i] + dp[k][i]);
		}
	}
	cout << dp[a][b] << '\n';
	return 0;
} 
