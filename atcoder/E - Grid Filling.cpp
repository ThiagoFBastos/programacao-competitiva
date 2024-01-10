#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

const int N = 3e2 + 10;

int frq[N][N][N];
int H, W, n;
int h, w;

int query(int x0, int y0, int x1, int y1) {
	int cnt = 0;
	for(int i = 1; i <= n; ++i) {
		int m = frq[x1][y1][i];
		m -= frq[x0 - 1][y1][i];
		m -= frq[x1][y0 - 1][i];
		m += frq[x0 - 1][y0 - 1][i];
		cnt += frq[H][W][i] - m > 0;
	}
	return cnt;
}

void solve() {

	cin >> H >> W >> n;
	cin >> h >> w;

	for(int i = 1; i <= H; ++i) {
		for(int j = 1; j <= W; ++j) {
			int v;
			cin >> v;
			++frq[i][j][v];
			for(int k = 1; k <= n; ++k) {
				frq[i][j][k] += frq[i - 1][j][k];
				frq[i][j][k] += frq[i][j - 1][k];
				frq[i][j][k] -= frq[i - 1][j - 1][k];
			}
		}
	}	

	for(int i = 0; i <= H - h; ++i) {
		for(int j = 0; j <= W - w; ++j)
			cout << query(i + 1, j + 1, i + h, j + w) << ' ';
		cout << '\n';
	}
}	

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}
