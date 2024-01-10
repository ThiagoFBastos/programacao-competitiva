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

const int mod = 1e9 + 7, N = 4e3 + 10;

int col[N], diagon[N];

void solve() {
	
	int h, w;

	cin >> h >> w;

	vector<string> g(h);

	for(auto& s : g) cin >> s;

	int dp;

	for(int i = 1; i <= h; ++i) {
		int row = 0;
		for(int j = 1; j <= w; ++j) {
			dp = i + j == 2;
			dp = (dp + (i64)row + (i64)col[j] + (i64)diagon[i - j + w]) % mod;
			row = (row + dp) % mod;
			col[j] = (col[j] + dp) % mod;
			diagon[i - j + w] = (diagon[i - j + w] + dp) % mod;
			if(g[i - 1][j - 1] == '#') row = col[j] = diagon[i - j + w] = 0;
		}
	}

	cout << dp << '\n';
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
