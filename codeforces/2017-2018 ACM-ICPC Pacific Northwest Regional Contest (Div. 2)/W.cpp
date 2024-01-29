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

const int N = 64;

i64 dp[N][N];
bool can[N][N];
int last[N];

void solve() {
	int n, m;

	cin >> n >> m;

	vector<string> g(n);
	for(auto& s : g) cin >> s;

	for(int i = 0; i < n; ++i) {
		last[i] = -1;
		for(int j = 0; j < m; ++j) {
			can[i][j] = g[i][j] != 'R';
			if(i > 0) can[i][j] = can[i][j] && can[i - 1][j];
			if(j > 0) can[i][j] = can[i][j] && can[i][j - 1];
			if(g[i][j] == 'B') last[i] = j;
		}
	}

	for(int j = m - 1; j >= 0; --j) {
		dp[0][j] = int(can[0][j]);
		if(g[0][j] == 'B') break;
	}
	
	for(int i = 1; i < n; ++i) {
		for(int j = m - 1; j >= 0; --j) {
			if(can[i][j]) {
				int _i;
				for(_i = i - 1; _i >= 0; --_i) {
					for(int k = j + 1; k < m; ++k) dp[i][j] += dp[_i][k];
					if(last[_i] > j) break;
				}
				if(_i < 0) ++dp[i][j];
			}
			if(g[i][j] == 'B') break;
		}
	}

	i64 ans = 0;
	int i;

	for(i = n - 1; i >= 0; --i) {
		for(int j = 0; j < m; ++j) ans += dp[i][j];
		if(last[i] != -1) break;
	}

	if(i < 0) ++ans;
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
