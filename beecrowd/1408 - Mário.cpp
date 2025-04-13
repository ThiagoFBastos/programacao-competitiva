#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
void read(int& n) {
	register int ch = getchar_unlocked();
	while(ch < 48) ch = getchar_unlocked();
	n ^= n;
	while(ch > 47) {
		n = (n << 3) + (n << 1) + ch - '0';
		ch = getchar_unlocked();
	}
}
int main() {
	const int MAXN = 1e5, INF = 1e9;
	int N, L, c[MAXN + 1];
	long long dp[MAXN + 1];
	c[0] = 0;
	while(true) {
		scanf("%d%d", &N, &L);
		if(N == 0 && L == 0) break;
		dp[0] = 0;
		for(int i = 1; i <= L; ++i) {
			read(c[i]);
			dp[i] = dp[i - 1] + c[i] - c[i - 1] - 1;
		}
		int ans = INF, low = 0, high = 0;
		for(int i = 1; i <= L; ++i) {
			while(high <= L && c[i] + N - 1 > c[high]) ++high;
			while(low <= L && c[low] < c[i] - N + 1) ++low;
			if(c[i] >= N)
				ans = min(0LL + ans, dp[i] - dp[low] + c[low] - c[i] + N - 1); 	
			if(c[i] + N - 1 <= INF) {
				if(high <= L && c[high] == c[i] + N - 1)
					ans = min(0LL + ans, dp[high] - dp[i]);
				else
					ans = min(0LL + ans, dp[high - 1] - dp[i] + c[i] + N - 1 - c[high - 1]); 
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}