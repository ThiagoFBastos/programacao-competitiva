#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100
#define MOD 1000000007
static inline void mult(int a[][MAXN], int b[MAXN][MAXN], int n) {
	int c[MAXN][MAXN];
	for(int k = 0; k < n; ++k) {
		for(int j = 0; j < n; ++j) {
			int r = 0;
			for(int i = 0; i < n; ++i)
				r = (r + 1LL * a[k][i] * b[i][j]) % MOD;
			c[k][j] = r;
		}
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			a[i][j] = c[i][j];
}
static inline void matrix_pow(int dest[][MAXN], int src[][MAXN], int n, int p) {
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			dest[i][j] = i == j;
	while(p > 0) {
		if(p & 1) mult(dest, src, n);
		mult(src, src, n);
		p >>= 1;
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int G[MAXN][MAXN], paths[MAXN][MAXN];
	int n, m, k;
	cin >> n >> m >> k;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			G[i][j] = 0;
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		++G[u - 1][v - 1];
	}
	matrix_pow(paths, G, n, k);
	cout << paths[0][n - 1] << '\n';
	return 0;
} 
