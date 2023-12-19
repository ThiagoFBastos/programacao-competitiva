#include "bits/stdc++.h"
using namespace std;
int k;
double ans[8][8], p[8][8];
void solve(double p[8][8], int x, int y) {
	double g[8][8];
	for(int i = 0; i < 8; ++i)
	for(int j = 0; j < 8; ++j)
		p[i][j] = g[i][j] = 0;
	p[x][y] = 1.0;
	for(int i = 0; i < k; ++i) {
		for(int x = 0; x < 8; ++x) {
			for(int y = 0; y < 8; ++y) {
				double S = p[x][y] / double((x > 0) + (y > 0) + (x < 7) + (y < 7));
				if(x) g[x - 1][y] += S;	
				if(y) g[x][y - 1] += S;
				if(x < 7) g[x + 1][y] += S;
				if(y < 7) g[x][y + 1] += S;
			}
		}
		for(int x = 0; x < 8; ++x)
		for(int y = 0; y < 8; ++y) {
			p[x][y] = g[x][y];
			g[x][y] = 0;
		}
	}
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);	
	cin >> k;
	for(int i = 0; i < 8; ++i)
	for(int j = 0; j < 8; ++j)
		ans[i][j] = 1.0;
	double K = 0;
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			solve(p, i, j);
			for(int x = 0; x < 8; ++x) for(int y = 0; y < 8; ++y) ans[x][y] *= 1 - p[x][y];
		}
	}
	for(int x = 0; x < 8; ++x) for(int y = 0; y < 8; ++y) K += ans[x][y];
	cout << fixed << setprecision(6) << K << '\n';
	return 0;
}
