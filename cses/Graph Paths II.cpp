#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 100
#define INF 0x1000000000000000LL
void minpath(ll a[][MAXN], ll b[][MAXN], int n) {
	ll c[MAXN][MAXN];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			c[i][j] = INF;
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			a[i][j] = c[i][j];
}
void matrix_pow(ll ans[][MAXN], ll G[MAXN][MAXN], int n, int p) {
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			ans[i][j] = G[i][j];
	--p;
	while(p > 0) {
		if(p & 1) minpath(ans, G, n);
		minpath(G, G, n);
		p >>= 1;
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll G[MAXN][MAXN], ans[MAXN][MAXN];
	int n, m, k;
	cin >> n >> m >> k;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			G[i][j] = INF;
	for(int i = 0; i < m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		G[u - 1][v - 1] = min(c + 0LL, G[u - 1][v - 1]);
	}
	matrix_pow(ans, G, n, k);
	if(ans[0][n - 1] == INF) cout << -1 << '\n';
	else cout << ans[0][n - 1] << '\n';
	return 0;
} 
