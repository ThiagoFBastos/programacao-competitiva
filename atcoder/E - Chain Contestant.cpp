#include "bits/stdc++.h"
using namespace std;

const int N = 1e3 + 1, mod = 998244353;

int dp[1 << 10][27], _[1 << 10][27];
int sdp[1 << 10];

int mod_sum(int x) {
	if(x >= mod) return x - mod;
	return x;
}

void solve() {
	int n;
	string s;
	cin >> n >> s;
	
	int ans = 0;
	
	sdp[0] = dp[0][0] = 1;
	
	for(int i = 1; i <= n; ++i) {
		int c = s[i - 1] - 'A';
		
		for(int k = 0; k < (1 << 10); ++k)
			for(int j = 0; j <= 26; ++j)
				_[k][j] = dp[k][j];
			
		for(int k = 0; k < (1 << 10); ++k) {
			if(k & 1 << c) {
				int x = _[k][c + 1];
				dp[k][c + 1] = mod_sum(dp[k][c + 1] + x);
				sdp[k] = mod_sum(sdp[k] + x);
			} else {
				dp[k | 1 << c][c + 1] = mod_sum(dp[k | 1 << c][c + 1] + sdp[k]);
				sdp[k | 1 << c] = mod_sum(sdp[k | 1 << c] + sdp[k]);
			}
		}
		
	}
	
	for(int i = 1; i < (1 << 10); ++i) ans = mod_sum(ans + sdp[i]);
	
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

