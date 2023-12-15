#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
void generate(ll *dp, int *a, int n) {
	int m = 1 << n;
	for(int k = 0; k < m; ++k)
		dp[k] = 0;
	for(int k = 1; k < m; ++k)
		dp[k] = a[__builtin_ctz(k & -k)] + dp[k - (k & -k)];
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, x, a[40];
	ll *dp1, *dp2;
	cin >> n >> x;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	int mid = (n + 1) / 2;
	dp1 = new ll[1 << mid];
	dp2 = new ll[1 << n - mid];
	generate(dp1, a, mid);
	generate(dp2, a + mid, n - mid);
	int m = 1 << mid, p = 1 << n - mid;
	int low = p, high = p;
	ll cnt = 0;
	sort(dp1, dp1 + m);
	sort(dp2, dp2 + p);
	for(int k = 0; k < m; ++k) {
		while(low > 0 && dp1[k] + dp2[low - 1] >= x) --low;
		while(high > low && dp1[k] + dp2[high - 1] > x) --high;
		cnt += high - low;
	}
	cout << cnt << '\n';
    return 0;
}
		
