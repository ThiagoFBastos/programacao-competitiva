#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2,sse3")
#include "bits/stdc++.h"
 
using namespace std;
 
const int mod = 1e9 + 7;
 
vector<vector<int>> prefix(string& s) {
	int n = s.size();
	vector<vector<int>> p(s.size());
	for(int k = 0; k < n; ++k) p[k].resize(26);
	fill(p[0].begin(), p[0].end(), 0);
	for(int k = 1; k < (int)s.size(); ++k) {
		for(int j = 0; j < 26; ++j) {
			int i = p[k - 1][s[k - 1] - 'A'];
			while(i && s[i] != j + 'A') i = p[i - 1][s[i - 1] - 'A'];
			p[k][j] = i + (s[i] == j + 'A');
		}
	}
	return p;
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	string s;
	cin >> n >> s;
	m = s.size();
	vector<vector<int>> dp1(n + 1);
	vector<int> dp2(n + 1);
	vector<vector<int>> p = prefix(s);
	for(int i = 0; i <= n; ++i) dp1[i].assign(m + 1, 0);
	dp1[0][0] = 1;
	dp2[0] = 0;
	for(int k = 1; k <= n; ++k) {
		dp2[k] = 26LL * (dp1[k - 1][m] + dp2[k - 1]) % mod;
		for(int i = 0; i < min(m, k); ++i) {
			for(int j = 0; j < 26; ++j) {
				if(j + 'A' == s[i]) {
					dp1[k][i + 1] += dp1[k - 1][i];
					if(dp1[k][i + 1] >= mod) dp1[k][i + 1] -= mod;
				} else {
					int h = p[i][j];
					dp1[k][h] += dp1[k - 1][i];
					if(dp1[k][h] >= mod) dp1[k][h] -= mod;
				}
			}
		}
	}
	dp2[n] += dp1[n][m];
	if(dp2[n] >= mod) dp2[n] -= mod;
	cout << dp2[n] << '\n';
	return 0;
}
