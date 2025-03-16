#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
typedef long long ll;
static inline void merge(double dest[], double src1[], double src2[], int n);
void merge(double dest[], double src1[], double src2[], int n) {
	int K = 1 << n;
	for(int i = 0; i < K; ++i) 
		dest[i] = min(src1[i], src2[i]);
	for(int i = 0; i < K; ++i)
		for(int S = i; S; S = (S - 1) & i)
			dest[i] = min(dest[i], src1[i ^ S] + src2[S]);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, c[5][2], f[10][2];
	double df[10][10], dc[5][10], dp[1024][10][5], cst[5][1024], r[5][1024]; 
	cin >> n >> m;
	for(int i = 0; i < m; ++i) 
		cin >> c[i][0] >> c[i][1];
	for(int i = 0; i < n; ++i) 
		cin >> f[i][0] >> f[i][1];
	for(int k = 0; k < n; ++k)
		for(int i = k + 1; i < n; ++i)
			df[k][i] = df[i][k] = hypot(f[i][0] - f[k][0], f[i][1] - f[k][1]);
	for(int k = 0; k < m; ++k)
		for(int i = 0; i < n; ++i)
			dc[k][i] = hypot(c[k][0] - f[i][0], c[k][1] - f[i][1]);
	int K = 1 << n;
	for(int i = 0; i < K; ++i)
		for(int j = 0; j < n; ++j)
			for(int k = 0; k < m; ++k)
				dp[i][j][k] = INT_MAX;
	for(int j = 0; j < n; ++j) {
		for(int k = 0; k < m; ++k) {
			dp[0][j][k] = 0;
			dp[1 << j][j][k] = dc[k][j];
		}
	}
	for(int k = 0; k < K; ++k) {
		for(int i = 0; i < m; ++i) {
			int r = 1;
			for(int j = 0; j < n; ++j) {
				if(k & r) {
					int s = 1, mask = k ^ r;
					for(int h = 0; h < n; ++h) {
						if(mask & s)
							dp[k][j][i] = min(dp[k][j][i], dp[mask][h][i] + df[j][h]);
						s <<= 1;
					}
				}
				r <<= 1;
			}
		}
	}
	for(int k = 0; k < m; ++k)
		cst[k][0] = 0;
	for(int k = 1; k < K; ++k) {
		for(int i = 0; i < m; ++i) {
			int r = 1;
			cst[i][k] = INT_MAX;
			for(int j = 0; j < n; ++j) {
				if(k & r)
					cst[i][k] = min(cst[i][k], dc[i][j] + dp[k][j][i]);
				r <<= 1;
			}
		}
	}
	if(m == 1) 
		cout << fixed << setprecision(2) << cst[0][K - 1] << '\n';
	else if(m == 2) {
		merge(r[0], cst[0], cst[1], n);
		cout << fixed << setprecision(2) << r[0][K - 1] << '\n';
	}
	else if(m == 3) {
		merge(r[0], cst[0], cst[1], n);
		merge(r[1], r[0], cst[2], n);
		cout << fixed << setprecision(2) << r[1][K - 1] << '\n';
	}
	else if(m == 4) {
		merge(r[0], cst[0], cst[1], n);
		merge(r[1], cst[2], cst[3], n);
		merge(r[2], r[0], r[1], n);
		cout << fixed << setprecision(2) << r[2][K - 1] << '\n';
	}
	else {
		merge(r[0], cst[0], cst[1], n);
		merge(r[1], cst[2], cst[3], n);
		merge(r[2], r[0], r[1], n);
		merge(r[3], r[2], cst[4], n);
		cout << fixed << setprecision(2) << r[3][K - 1] << '\n';
	}
    return 0;
}