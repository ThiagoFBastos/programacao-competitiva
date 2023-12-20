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
#define MAXN 5000
#define INF 0x1000000000000LL
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int c[MAXN], n, j;
	ll dp[MAXN][2], sum = 0;
	cin >> n;
	for(int k = 0; k < n; ++k) {cin >> c[k]; sum += c[k];}
	if(n & 1) {
		j = 0;
		for(int k = 0; k < n; ++k)
			dp[k][0] = c[k];
	}
	else {
		j = 1;
		for(int k = 0; k < n; ++k)
			dp[k][1] = c[k];
	}
	for(int k = n - 1; k > 0; --k) {
		++j;
		int a = j & 1, b = j + 1 & 1;
		for(int i = 0; i < k; ++i) 
			dp[i][a] = -INF;
		for(int i = 0; i < k; ++i)
			dp[i][a] = max(c[i] - dp[i + 1][b], dp[i][a]);
		for(int i = 0; i < k; ++i)
			dp[i][a] = max(dp[i][a], c[i + n - k] - dp[i][b]);
	}
	cout << (sum + dp[0][0]) / 2 << '\n';
	return 0;
} 
