#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("popcnt")
#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

const int N = 1e2;

int n, t, l;
vector<ii> ed;
int A[N][N], B[N][N];

void mul(int a[][N], int b[][N], int n) {
	int c[N][N];
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			c[i][j] = INF;
			for(int k = 0; k < n; ++k)
				c[i][j] = min(c[i][j], max(a[i][k], b[k][j]));
		}
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			a[i][j] = c[i][j];
}

void matrix_pow(int b[][N], int a[][N], int n, int p) {
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			b[i][j] = i == j ? -1 : INF;
	for(; p > 0; p >>= 1) {
		if(p & 1) mul(b, a, n);
		mul(a, a, n);
	}
}

void solve() {
	cin >> n >> t >> l;

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			A[i][j] = INF;

	for(int i = 1; i <= t; ++i) {
		int a, b;
		cin >> a >> b;
		A[a-1][b-1] = i;
	}
	
	matrix_pow(B, A, n, l);

	for(int i = 0; i < n; ++i) {
		if(B[0][i] == INF) {
			cout << "-1 ";
			continue;
		}
		cout << B[0][i] << ' ';
	}
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}sss
