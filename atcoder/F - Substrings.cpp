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

const int mod = 1e9 + 7;

void solve() {
	string s;

	cin >> s;
	
	int n = s.size();
	vector<int> dp(n + 2, 0);
	vector<array<int, 26>> nxt(n);
	array<int, 26> last;

	last.fill(n + 1);

	for(int i = n - 1; i >= 0; --i) {
		nxt[i] = last;
		last[s[i] - 'a'] = i;
	}

	for(int i = 0; i < 26; ++i) dp[last[i]] = 1;

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < 26; ++j) {
			int k = nxt[i][j];
			if(k == i + 1) k = nxt[k][j];
			dp[k] += dp[i];
			if(dp[k] >= mod) dp[k] -= mod;
		}
	}

	i64 cnt = 0;

	for(int i = 0; i < n; ++i) cnt += dp[i];

	cout << cnt % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
