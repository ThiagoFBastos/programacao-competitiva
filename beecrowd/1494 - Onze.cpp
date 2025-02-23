#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 102, MOD = 1e9 + 7;
static int fat[MAXN], inv[MAXN], d[10];
static inline long long invmod(long long n);
static inline int permutations(int n, int m, int S);
long long invmod(long long n) {
	long long r = 1;
	int p = MOD - 2;
	while(p > 0) {
		if(p & 1) r = r * n % MOD;	
		n = n * n % MOD;
		p >>= 1;
	}
	return r;
}
int permutations(int n, int m, int S) {
	long long dp[11][11][52][52];
	for(int k = 0; k < 11; ++k)
		for(int i = 0; i < 11; ++i)
			for(int j = 0; j <= n; ++j)
				for(int h = 0; h <= m; ++h)
					dp[k][i][j][h] = 0;
	dp[0][0][0][0] = 1;
	int t = 0;
	for(int k = 0; k <= 9; ++k) {
		if(d[k]) {
			int N = d[k];
			for(int i = 0; i <= N; ++i) {
				int M = N - i;
				for(int a = 0; a < 11; ++a) {
					for(int b = 0; b + i <= n; ++b) {
						if(t - b < 0) break;
						int c = (a + i * k) % 11;
						long long p;
						dp[k + 1][c][b + i][M + t - b] += dp[k][a][b][t - b] * inv[i] % MOD * inv[M] % MOD;
						if(dp[k + 1][c][b + i][M + t - b] >= MOD) dp[k + 1][c][b + i][M + t - b] -= MOD;
					}
				}
			}
		}
		for(int i = 0; i <= n; ++i) {
			if(t < i) break;
			for(int j = 0; j < 11; ++j) {
				dp[k + 1][j][i][t - i] += dp[k][j][i][t - i];
				if(dp[k + 1][j][i][t - i] >= MOD) dp[k + 1][j][i][t - i] -= MOD;
			}
		}
		t += d[k];
	}
	int count = 0;
	for(int i = 0; i < 11; ++i) {
		if((10 * S - 9 * i) % 11 == 0) {
			count += dp[10][i][n][m] * fat[n] % MOD * fat[m] % MOD;
			if(count >= MOD) count -= MOD;
		}
	}
	return count;
}
int main() {
	char S[MAXN];
	fat[0] = inv[0] = 1;
	for(long long k = 1; k < MAXN; ++k) {
		fat[k] = k * fat[k - 1] % MOD;
		inv[k] = invmod(fat[k]);
	}
	while(scanf("%s", S) != EOF) {
		int n = strlen(S), s = 0, count;
		memset(d, 0, sizeof d);
		for(int i = 0; i < n; ++i) {
			++d[S[i] - '0'];
			s += S[i] - '0';
		}
		s %= 11;
		count = permutations((n + 1) / 2, n / 2, s);
		if(d[0]--) count -= permutations(n / 2, (n - 1) / 2, s);
		printf("%d\n", (count + MOD) % MOD);
	}
	return 0;
}