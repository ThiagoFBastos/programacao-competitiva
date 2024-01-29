#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int N = 300;

int n, p[N][4];

void sim() {
	string o;
	int x[2] = {0}, g[12][12][12][12], f = 0;
	
	for(int i = 0; i <= 1 + n; ++i)
	for(int j = 0; j <= 1 + n; ++j)
	for(int k = 0; k <= 1 + n; ++k)
	for(int l = 0; l <= 1 + n; ++l)
		g[i][j][k][l] = 0;
		
	int K = 2 * (n * n - n), sq = 0;
	
	for(int i = 0; i < K; ++i)
	for(int j = 0; j < 4; ++j)
		cin >> p[i][j];	
	
	for(int i = 0; i < K; ++i) {
		int x1 = p[i][0], y1 = p[i][1], x2 = p[i][2], y2 = p[i][3];
		
		if(x1 > x2 || y1 > y2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		
		int s = 0;
		
		g[x1][y1][x2][y2] = 1;
		
		for(int x = 1; x <= n; ++x) {
			for(int y = 1; y <= n; ++y) {
				int cnt = g[x][y][x][y + 1];
				cnt += g[x][y][x + 1][y];
				cnt += g[x + 1][y][x + 1][y + 1];
				cnt += g[x][y + 1][x + 1][y + 1];
				s += cnt == 4;
			}
		}
	
		o += 'A' + f;
		if(s == sq) f ^= 1;
		else x[f] += s - sq;
		
		sq = s;
	}
	
	cout << o << '\n';
	cout << x[0] << ' ' << x[1] << '\n';
}

void solve() {
	cin >> n;
	sim();
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
 	return 0;
}


