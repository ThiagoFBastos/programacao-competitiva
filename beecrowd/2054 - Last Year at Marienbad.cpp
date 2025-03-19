#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

int j[2][4][6][8][10][12];

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	for(int a = 0; a <= 1; ++a) {
		for(int b = 0; b <= 3; ++b) {
			for(int c = 0; c <= 5; ++c) {
				for(int d = 0; d <= 7; ++d) {
					for(int e = 0; e <= 9; ++e) {
						for(int f = 0; f <= 11; ++f) {
							if(a|b|c|d|e|f) {
								int _a = 1, _b = 1, _c = 1, _d = 1, _e = 1, _f = 1;
								j[a][b][c][d][e][f] = 1;
								for(int k = 0; k <= a; ++k) _a &= j[k][b][c][d][e][f];
								for(int k = 0; k <= b; ++k) _b &= j[a][k][c][d][e][f];
								for(int k = 0; k <= c; ++k) _c &= j[a][b][k][d][e][f];
								for(int k = 0; k <= d; ++k) _d &= j[a][b][c][k][e][f];
								for(int k = 0; k <= e; ++k) _e &= j[a][b][c][d][k][f];
								for(int k = 0; k <= f; ++k) _f &= j[a][b][c][d][e][k];
								j[a][b][c][d][e][f] = 1 ^ (_a & _b & _c & _d & _e & _f);
							}
							else
								j[a][b][c][d][e][f] = 1;
						}
					}
				}
			}
		}
	}

	int t;

	cin >> t;

	for(int i = 1; i <= t; ++i) {
		int a, b, c, d, e, f;
		cin >> a >> b >> c >> d >> e >> f;
		cout << "Instancia " << i << '\n';
		cout << (j[a][b][c][d][e][f] ? "sim" : "nao") << '\n';
		if(i < t) cout << '\n';
	} 
	
	return 0;
}