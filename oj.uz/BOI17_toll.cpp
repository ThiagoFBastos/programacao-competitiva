#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
const int N = 5e4 + 10, K = 5, L = 16;
 
int adj[N][K][K], n, r, m, o, cost[L][N][K][K];
 
void min_path(int c[][K], int a[][K], int b[][K]) {
	int d[K][K];
 
	for(int i = 0; i < r; ++i)
	for(int j = 0; j < r; ++j)
		d[i][j] = INF;
	
	for(int k = 0; k < r; ++k)
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < r; ++j)
				d[i][j] = min(d[i][j], a[i][k] + b[k][j]);
 
	for(int i = 0; i < r; ++i)
	for(int j = 0; j < r; ++j)
		c[i][j] = d[i][j];
}
 
void query(int a[][K], int s, int t) {
	for(int i = L - 1; i >= 0; --i) {
		if(s + (1 << i) <= t) {
			min_path(a, a, cost[i][s]);
			s += 1 << i;
		}
	}
}
 
void solve() {
	cin >> r >> n >> m >> o;
 
	n = (n - 1) / r + 1;
 
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < r; ++j)
	for(int k = 0; k < r; ++k)
		adj[i][j][k] = INF;
 
	for(int i = 0; i < m; ++i) {
		int a, b, t;
		cin >> a >> b >> t;
		adj[a / r][a % r][b % r] = t;
	}
 
	for(int i = 0; i < n; ++i)
	for(int j = 0; j < r; ++j)
	for(int k = 0; k < r; ++k)
		cost[0][i][j][k] = adj[i][j][k];
 
	for(int i = 1; (1 << i) < n; ++i)
		for(int j = 0; j + (1 << i) < n; ++j)
			min_path(cost[i][j], cost[i - 1][j], cost[i - 1][j + (1 << (i - 1))]);
 
	for(int i = 0; i < o; ++i) {
		int a, b, A[K][K];
 
		cin >> a >> b;
 
		if(a / r == b / r) {
			cout << "-1\n";
			continue;
		}
 
		for(int k = 0; k < r; ++k)
			for(int j = 0; j < r; ++j)
				A[k][j] = k == a % r ? adj[a / r][k][j] : INF;
		
		query(A, a / r + 1, b / r);
 
		cout << (A[a % r][b % r] == INF ? -1 : A[a % r][b % r]) << '\n';
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
